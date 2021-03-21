#include "robot/robot_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/devices/controller_class.hpp"
#include "robot/devices/timer_class.hpp"
#include "robot/subsystems/holonomic_class.hpp"
#include "robot/subsystems/manipulator.hpp"
#include "robot/subsystems/odometry_class.hpp"

Holonomic::Holonomic(Robot &p_robot):
m_robot(p_robot),
m_front_left_motor(m_robot.add_motor("Front Left Base", 15, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false)),
m_front_right_motor(m_robot.add_motor("Front Right Base", 16, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, true)),
m_back_left_motor(m_robot.add_motor("Back Left Base", 5, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false)),
m_back_right_motor(m_robot.add_motor("Back Right Base", 6, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, true)),
m_timer(*new Timer()),
m_movement_timer(*new Timer())
{
}

void Holonomic::set_base_movement(double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration){
    m_desired_trajectory.m_translation_velocity = p_translational_velocity;
    m_desired_trajectory.m_orientation_velocity = p_turning_velocity;
    m_desired_trajectory.m_translation_angle = p_orientation;
    m_desired_trajectory.m_duration = p_duration;

    m_timer.reset_timer();
    m_timer.set_flag_delay(m_desired_trajectory.m_duration);

    m_movement_complete = false;
    m_movement_ending = false;

    m_status = BASE_TRANSLATE;
}

void Holonomic::set_base_movement(Autonomous_Base_Status p_base_status, double p_delay, double p_x_position, double p_y_position, double p_orientation){
    m_status = p_base_status;

    m_desired_trajectory.m_x_position = p_x_position;
    m_desired_trajectory.m_y_position = p_y_position;
    m_desired_trajectory.m_orientation = p_orientation;

    m_movement_complete = false;
    m_movement_ending = false;
}

void Holonomic::autonomous(){
    Odometry odometry = m_robot.get_odometry();

    if(m_status == BASE_ORIENTATION){
        
        m_orientation_error = m_desired_trajectory.m_orientation - odometry.get_total_orientation();
        m_orientation_integral += m_orientation_error;
        m_orientation_derivative = m_orientation_error - m_orientation_previous_error;
        m_orientation_previous_error = m_orientation_error;

        if(m_orientation_error == 0 || abs(m_orientation_error) > 2){
            m_orientation_integral = 0;
        }

        double velocity = (m_Kp_orientation * m_orientation_error) + (m_Ki_orientation * m_orientation_integral) + (m_Kp_orientation * m_orientation_derivative);

        
        if(velocity > 90)// Max Vel
            velocity = 90;
        else if(velocity < -90)
            velocity = -90;


        if(abs(velocity) < 4 && !m_movement_ending){
            m_movement_timer.set_flag_delay(400);  
            m_movement_ending = true;    
        }

        if(m_movement_timer.get_preform_action()){
            m_front_left_motor = 0;
            m_front_right_motor = 0;
            m_back_left_motor = 0;
            m_back_right_motor = 0;

            m_movement_complete = true;
            return;
        }

        m_front_left_motor = -velocity;
        m_front_right_motor = velocity;
        m_back_left_motor = -velocity;
        m_back_right_motor = velocity;
    }
    else{
        if(m_timer.get_flag_remaining() == 0){
            m_front_left_motor = 0;
            m_front_right_motor = 0;
            m_back_left_motor = 0;
            m_back_right_motor = 0;

            m_movement_complete = true;
            return;
        }

    double speed_up_coefficient = m_timer.get_elapsed_time() * 0.002;
    double speed_down_coefficient = m_timer.get_flag_remaining() * 0.002;

    double motor_coefficient;
    if (speed_up_coefficient < 1.0 && speed_up_coefficient < speed_down_coefficient)
        motor_coefficient = speed_up_coefficient;
    else if (speed_down_coefficient < 1.0 && speed_down_coefficient < speed_up_coefficient)
        motor_coefficient = speed_down_coefficient;
    else if (speed_up_coefficient >= 1.0 && speed_down_coefficient >= 1.0)
        motor_coefficient = 1.0;

    m_front_left_motor = motor_coefficient * (cos((m_desired_trajectory.m_translation_angle / 180.0 * M_PI) + (M_PI / 4.0)) * m_desired_trajectory.m_translation_velocity - m_desired_trajectory.m_orientation_velocity);
    m_front_right_motor = motor_coefficient * (sin((m_desired_trajectory.m_translation_angle / 180.0 * M_PI) + (M_PI / 4.0)) * m_desired_trajectory.m_translation_velocity + m_desired_trajectory.m_orientation_velocity);
    m_back_left_motor = motor_coefficient * (sin((m_desired_trajectory.m_translation_angle / 180.0 * M_PI) + (M_PI / 4.0)) * m_desired_trajectory.m_translation_velocity - m_desired_trajectory.m_orientation_velocity);
    m_back_right_motor = motor_coefficient * (cos((m_desired_trajectory.m_translation_angle / 180.0 * M_PI) + (M_PI / 4.0)) * m_desired_trajectory.m_translation_velocity + m_desired_trajectory.m_orientation_velocity);
    }
}

void Holonomic::driver_control(){
    CONTROLLER::Controller &l_main_controller = m_robot.get_main_controller();
    CONTROLLER::Controller &l_partner_controller = m_robot.get_partner_controller();

    int l_translation_coefficient;
    int l_orientation_coefficient;
    if (m_robot.get_manipulator().is_scoring()){
        l_translation_coefficient = 100;
        l_orientation_coefficient = 50;
    }
    else if (l_main_controller.ButtonL2.get_state() && l_main_controller.ButtonR2.get_state()){
        l_translation_coefficient = 100;
        l_orientation_coefficient = 100;
    }
    else if (l_main_controller.ButtonL2.get_state()){
        l_translation_coefficient = 100;
        l_orientation_coefficient = 200;
    }
    else if (l_main_controller.ButtonR2.get_state()){
        l_translation_coefficient = 200;
        l_orientation_coefficient = 100;
    }
    else{
        l_translation_coefficient = 200;
        l_orientation_coefficient = 200;
    }

    m_front_left_motor.set_desired_velocity(l_translation_coefficient * l_main_controller.Axis3.get_percent() + l_translation_coefficient * l_main_controller.Axis4.get_percent() + (l_orientation_coefficient * l_main_controller.Axis1.get_percent()));
    m_front_right_motor.set_desired_velocity(l_translation_coefficient * l_main_controller.Axis3.get_percent() - l_translation_coefficient * l_main_controller.Axis4.get_percent() - (l_orientation_coefficient * l_main_controller.Axis1.get_percent()));
    m_back_left_motor.set_desired_velocity(l_translation_coefficient * l_main_controller.Axis3.get_percent() - l_translation_coefficient * l_main_controller.Axis4.get_percent() + (l_orientation_coefficient * l_main_controller.Axis1.get_percent()));
    m_back_right_motor.set_desired_velocity(l_translation_coefficient * l_main_controller.Axis3.get_percent() + l_translation_coefficient * l_main_controller.Axis4.get_percent() - (l_orientation_coefficient * l_main_controller.Axis1.get_percent()));
}

void Holonomic::initialize(){
    m_front_left_motor.reset_position();
    m_front_right_motor.reset_position();
    m_back_left_motor.reset_position();
    m_back_right_motor.reset_position();
}

int Holonomic::task(){
    if (m_robot.get_robot_state() == ROBOT_DRIVER_CONTROL){
        driver_control();
    }
    else if (m_robot.get_robot_state() == ROBOT_AUTONOMOUS){
        autonomous();
    }
    return 0;
}
