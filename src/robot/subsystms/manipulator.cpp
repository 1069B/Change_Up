#include "robot/robot_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/devices/controller_class.hpp"
#include "robot/devices/timer_class.hpp"

#include "robot/subsystems/manipulator.hpp"

#include "robot/sensors/optical_class.hpp"
#include "robot/sensors/digital_class.hpp"

#include "robot/graphical_interface/screen_class.hpp"
#include "robot/graphical_interface/button_class.hpp"
#include "robot/graphical_interface/switch_class.hpp"
#include "robot/graphical_interface/roller_class.hpp"

Manipulator::Manipulator(Robot& p_robot):
m_robot(p_robot),
m_intake_timer(*new Timer()),
m_lift_timer(*new Timer()),
m_left_intake(m_robot.add_motor("Left Intake", 12, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_COAST, false)),
m_right_intake(m_robot.add_motor("Right Intake", 19, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_COAST, true)),
m_initial_roller(m_robot.add_motor("Initial Rollers", 9, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_BRAKE, true)),
m_secondary_roller(m_robot.add_motor("Second Rollers", 10, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_COAST, true)),
m_intake_sensor(m_robot.add_optical("Intake Sensor", 20)),
m_sorting_sensor(m_robot.add_optical("Sorting Sensor Score", 2)),
m_scoring_left_sensor(m_robot.add_digital("Scoring Left", 2)),
m_scoring_right_sensor(m_robot.add_digital("Scoring Right", 1))
{
    	
}

void Manipulator::initialize(){
    if(m_robot.get_alliance() == ROBOT_SKILLS || m_robot.get_alliance() == ROBOT_RED){
        m_intake_sensor.set_signature_1(12, 78);
        m_intake_sensor.set_signature_2(190, 210);
        m_intake_sensor.set_signature_3(0, 360, 0, 10);

        m_sorting_sensor.set_signature_1(0, 20);// Scoring
        m_sorting_sensor.set_signature_2(206, 226);// Eject
    }
    else if(m_robot.get_alliance() == ROBOT_BLUE){
        m_intake_sensor.set_signature_1(190, 210);

        m_sorting_sensor.set_signature_1(206, 226);// Scoring
        m_sorting_sensor.set_signature_2(0, 20);// Eject
    }
}

void Manipulator::set_mode(Manipulator_Mode p_mode){
    m_mode = p_mode;
    if(m_mode == MANIPULATOR_FEILD){
        
    }
    else if(m_mode == MANIPULATOR_GOAL_SCORE){
        m_lift_status = LIFT_WAITING;
    }
    else if(m_mode == MANIPULATOR_GOAL_REMOVE){
        m_lift_status = LIFT_WAITING;
    } 
}

void Manipulator::autonomous_feild(){
    if(!(m_ball_positions.m_scoreing == BALL_DESIRED && m_ball_positions.m_sorting == BALL_DESIRED) && m_ball_positions.m_intakes == BALL_DESIRED){
        m_left_intake.set_desired_velocity(600);
        m_right_intake.set_desired_velocity(600);

        m_intake_position = INTAKE_FULLY_EXTENDED;
        m_intake_status = INTAKE_AUTO_INTAKE;

        if(m_ball_positions.m_sorting == BALL_NONE){
            m_initial_roller.set_desired_velocity(200);
            m_lift_status = LIFT_INTAKING;
        }
        else
            m_lift_status = LIFT_SENSORS;
    }
    else if(!(m_ball_positions.m_scoreing == BALL_DESIRED || m_ball_positions.m_sorting == BALL_DESIRED) && m_ball_positions.m_intakes == BALL_OPPOSING){
        m_left_intake.set_desired_velocity(600);
        m_right_intake.set_desired_velocity(600);

        m_intake_position = INTAKE_FULLY_EXTENDED;
        m_intake_status = INTAKE_AUTO_INTAKE;

        if(m_ball_positions.m_sorting == BALL_NONE){
            m_initial_roller.set_desired_velocity(200);
            m_lift_status = LIFT_INTAKING;
        }
        else
            m_lift_status = LIFT_SENSORS;
    }
    else if(m_intake_status == INTAKE_AUTO_INTAKE && (m_ball_positions.m_intakes != BALL_OPPOSING && m_ball_positions.m_intakes != BALL_DESIRED)){
        m_intake_status = INTAKE_AUTO_OPEN;
        m_intake_position = INTAKE_FULLY_EXTENDED;

        m_left_intake.set_desired_velocity(-300);
        m_right_intake.set_desired_velocity(-300);

        if(m_ball_positions.m_sorting == BALL_NONE){
            m_initial_roller.set_desired_velocity(200);
            m_lift_status = LIFT_INTAKING;
        }
        else
            m_lift_status = LIFT_SENSORS;

        m_intake_timer.set_flag_delay(500);
    }
    else if(m_intake_status == INTAKE_AUTO_OPEN && m_intake_timer.get_preform_action()){
        m_left_intake.set_desired_velocity(0);
        m_right_intake.set_desired_velocity(0);

        m_intake_status = INTAKE_STATIONARY;
        m_intake_position = INTAKE_OPEN;
    }

    if(m_ball_positions.m_scoreing == BALL_DESIRED){
        m_secondary_roller.set_desired_velocity(0);
        if(m_ball_positions.m_sorting == BALL_OPPOSING){
            m_initial_roller.set_desired_velocity(200);
            m_secondary_roller.set_desired_velocity(20);
        }
    }
    else{
        if(m_ball_positions.m_sorting == BALL_DESIRED){
            m_initial_roller.set_desired_velocity(200);
            m_secondary_roller.set_desired_velocity(600);
        } 
        else if(m_ball_positions.m_sorting == BALL_OPPOSING){
            m_initial_roller.set_desired_velocity(200);
            m_secondary_roller.set_desired_velocity(-600);
        }
        else{
            if(m_lift_status == LIFT_SENSORS)
                m_initial_roller.set_desired_velocity(0);
            m_secondary_roller.set_desired_velocity(0);
        }
    }
}

void Manipulator::autonomous_goal_score(){
    if(m_intake_position != INTAKE_STORED){
        m_left_intake.set_desired_velocity(-300);
        m_right_intake.set_desired_velocity(-300);
        if(m_intake_position == INTAKE_OPEN)
            m_intake_timer.set_flag_delay(250);//TODO: Refine Value
        else if(m_intake_position == INTAKE_FULLY_EXTENDED)
            m_intake_timer.set_flag_delay(500);//TODO: Refine Value

        m_intake_status = INTAKE_AUTO_OPEN;
    }
    else if(m_intake_position != INTAKE_STORED && m_intake_status == INTAKE_AUTO_OPEN && m_intake_timer.get_preform_action()){
        m_left_intake.set_desired_velocity(0);
        m_right_intake.set_desired_velocity(0);

        m_intake_position = INTAKE_STORED;
        m_intake_status = INTAKE_STATIONARY;
    }

    if(m_ball_positions.m_scoreing == BALL_DESIRED && m_ball_positions.m_intakes == BALL_GOAL && m_lift_status != LIFT_SCORING){
        m_secondary_roller.set_desired_velocity(600);
        m_lift_status == LIFT_SCORING;
        m_lift_timer.set_flag_delay(750);
    }
    else if(m_ball_positions.m_intakes == BALL_GOAL && m_lift_status == LIFT_SCORING && !m_lift_timer.get_preform_action()){}
    else if(m_ball_positions.m_intakes == BALL_GOAL && m_lift_status == LIFT_SCORING && m_lift_timer.get_preform_action()){
        m_secondary_roller.set_desired_velocity(0);
        m_lift_status == LIFT_WAITING;
    }
    else{
        if(m_ball_positions.m_scoreing == BALL_DESIRED){
            m_secondary_roller.set_desired_velocity(0);
            if(m_ball_positions.m_sorting == BALL_OPPOSING){
                m_initial_roller.set_desired_velocity(200);
                m_secondary_roller.set_desired_velocity(20);
            }
        }
        else{
            if(m_ball_positions.m_sorting == BALL_DESIRED){
                m_initial_roller.set_desired_velocity(200);
                m_secondary_roller.set_desired_velocity(600);
            } 
            else if(m_ball_positions.m_sorting == BALL_OPPOSING){
                m_initial_roller.set_desired_velocity(200);
                m_secondary_roller.set_desired_velocity(-600);
            }
            else{
                m_initial_roller.set_desired_velocity(0);
                m_secondary_roller.set_desired_velocity(0);
            }
        }
    }
}

void Manipulator::autonomous_goal_remove(){
    m_left_intake.set_desired_velocity(600);
    m_right_intake.set_desired_velocity(600);
    m_intake_position = INTAKE_FULLY_EXTENDED;
    m_intake_status = INTAKE_AUTO_INTAKE;

    if(m_ball_positions.m_scoreing == BALL_DESIRED && m_ball_positions.m_intakes == BALL_GOAL && m_lift_status != LIFT_SCORING){
        m_secondary_roller.set_desired_velocity(600);
        m_lift_status == LIFT_SCORING;
        m_lift_timer.set_flag_delay(750);
    }
    else if(m_ball_positions.m_intakes == BALL_GOAL && m_lift_status == LIFT_SCORING && !m_lift_timer.get_preform_action()){}
    else if(m_ball_positions.m_intakes == BALL_GOAL && m_lift_status == LIFT_SCORING && m_lift_timer.get_preform_action()){
        m_secondary_roller.set_desired_velocity(0);
        m_lift_status == LIFT_WAITING;
    }
    else{
        if(m_ball_positions.m_scoreing == BALL_DESIRED){
            m_secondary_roller.set_desired_velocity(0);
            if(m_ball_positions.m_sorting == BALL_OPPOSING){
                m_initial_roller.set_desired_velocity(200);
                m_secondary_roller.set_desired_velocity(20);
            }
        }
        else{
            if(m_ball_positions.m_sorting == BALL_DESIRED){
                m_initial_roller.set_desired_velocity(200);
                m_secondary_roller.set_desired_velocity(600);
            } 
            else if(m_ball_positions.m_sorting == BALL_OPPOSING){
                m_initial_roller.set_desired_velocity(200);
                m_secondary_roller.set_desired_velocity(-600);
            }
            else{
                m_initial_roller.set_desired_velocity(200);
                m_secondary_roller.set_desired_velocity(0);
            }
        }
    }
}

void Manipulator::autonomous(){
    /* Detects Current Ball Position */
    bool l_ball_at_top = m_scoring_left_sensor.get_value() || m_scoring_right_sensor.get_value();
    if(l_ball_at_top)
        m_ball_positions.m_scoreing = BALL_DESIRED;
    else
        m_ball_positions.m_scoreing = BALL_NONE;

    if(m_sorting_sensor.is_signature_1())
        m_ball_positions.m_sorting = BALL_DESIRED;
    else if(m_sorting_sensor.is_signature_2())
        m_ball_positions.m_sorting = BALL_OPPOSING;
    else
        m_ball_positions.m_sorting = BALL_NONE;

    if(m_intake_sensor.is_signature_1())
        m_ball_positions.m_sorting = BALL_DESIRED;
    else if(m_intake_sensor.is_signature_2())
        m_ball_positions.m_sorting = BALL_OPPOSING;
    else if(m_intake_sensor.is_signature_3()){
        m_ball_positions.m_sorting = BALL_GOAL;
    }
    else
        m_ball_positions.m_sorting = BALL_NONE;


    if(m_mode == MANIPULATOR_FEILD)
        autonomous_feild();
    else if(m_mode == MANIPULATOR_GOAL_SCORE)
        autonomous_goal_score();
    else if(m_mode == MANIPULATOR_GOAL_REMOVE)
        autonomous_goal_remove();
}

void Manipulator::driver_control(){
    if(m_robot.get_partner_controller().ButtonR1.get_state()){
        m_initial_roller.set_desired_velocity(0);
		m_secondary_roller.set_desired_velocity(600);
        m_lift_status = LIFT_NO_RESTRICTIONS;
    }
    else if(m_sorting_sensor.is_signature_2()){
        if(m_scoring_left_sensor.get_value() || m_scoring_right_sensor.get_value()){
            m_initial_roller.set_desired_velocity(200);
			m_secondary_roller.set_desired_velocity(0);//TODO: Add positive spin so rollers don't move
            m_lift_status = LIFT_TOP_CONTROLLED;
        }
        else{
            m_initial_roller.set_desired_velocity(200);
			m_secondary_roller.set_desired_velocity(-600);
            m_lift_status = LIFT_TOP_CONTROLLED;
        }
    }
    else if(m_sorting_sensor.is_signature_1()){
        if(m_scoring_left_sensor.get_value() && m_scoring_right_sensor.get_value()){
            m_initial_roller.set_desired_velocity(0);
			m_secondary_roller.set_desired_velocity(0);
            m_lift_status = LIFT_BOTH_CONTROLLED;
        }
        else{
            m_initial_roller.set_desired_velocity(200);
			m_secondary_roller.set_desired_velocity(600);
            m_lift_status = LIFT_NO_RESTRICTIONS;
        }
    }
    else if(m_scoring_left_sensor.get_value() && m_scoring_right_sensor.get_value() && (m_robot.get_partner_controller().Axis2.get_percent() < -0.10 || 0.10 < m_robot.get_partner_controller().Axis2.get_percent())){
        m_initial_roller.set_desired_velocity(m_robot.get_partner_controller().Axis2.get_percent()*200);
		m_secondary_roller.set_desired_velocity(0);
        m_lift_status = LIFT_TOP_CONTROLLED;
    }
    else if(m_robot.get_partner_controller().Axis2.get_percent() < -0.10 || 0.10 < m_robot.get_partner_controller().Axis2.get_percent()){
        m_initial_roller.set_desired_velocity(m_robot.get_partner_controller().Axis2.get_percent() * 200);
		m_secondary_roller.set_desired_velocity(m_robot.get_partner_controller().Axis2.get_percent() * 600);
        m_lift_status = LIFT_NO_RESTRICTIONS;
    }
    else{
        m_initial_roller.set_desired_velocity(0);
        m_secondary_roller.set_desired_velocity(0);
        m_lift_status = LIFT_NO_RESTRICTIONS;
    }

    if(m_robot.get_partner_controller().Axis3.get_percent() < -0.10 || 0.10 < m_robot.get_partner_controller().Axis3.get_percent()){
        m_intake_status = INTAKE_USER_BASED;
        m_left_intake.set_desired_velocity(m_robot.get_partner_controller().Axis3.get_percent() * 600);
        m_right_intake.set_desired_velocity(m_robot.get_partner_controller().Axis3.get_percent() * 600);

        if(m_lift_status == LIFT_NO_RESTRICTIONS || m_lift_status == LIFT_TOP_CONTROLLED)
            m_initial_roller.set_desired_velocity(200);
    }
    else if(m_robot.get_partner_controller().ButtonL1.get_state()){
        m_intake_status = INTAKE_USER_BASED;
        m_left_intake.set_desired_velocity(600);
        m_right_intake.set_desired_velocity(600);
        
        if(m_lift_status == LIFT_NO_RESTRICTIONS || m_lift_status == LIFT_TOP_CONTROLLED)
            m_initial_roller.set_desired_velocity(200);
    }
    else if(m_robot.get_partner_controller().ButtonL2.get_state()){
        m_intake_status = INTAKE_USER_BASED;
        m_left_intake.set_desired_velocity(-300);
        m_right_intake.set_desired_velocity(-300);
    }
    else if(m_intake_sensor.is_signature_1()){
        m_intake_status = INTAKE_AUTO_INTAKE;
        m_left_intake.set_desired_velocity(600);
        m_right_intake.set_desired_velocity(600);

        if(m_lift_status == LIFT_NO_RESTRICTIONS || m_lift_status == LIFT_TOP_CONTROLLED)
            m_initial_roller.set_desired_velocity(200);
    }
    else if(m_intake_status == INTAKE_AUTO_INTAKE && !m_intake_sensor.is_signature_1()){
        m_intake_status = INTAKE_AUTO_OPEN;
        m_left_intake.set_desired_velocity(-300);
        m_right_intake.set_desired_velocity(-300);

        m_intake_timer.set_flag_delay(500);
    }
    else if(m_intake_status == INTAKE_AUTO_OPEN && m_intake_timer.get_preform_action()){
        m_left_intake.set_desired_velocity(0);
        m_right_intake.set_desired_velocity(0);
        m_intake_status = INTAKE_STATIONARY;
    }
    else if(m_intake_status == INTAKE_AUTO_OPEN){
        if(m_lift_status == LIFT_NO_RESTRICTIONS || m_lift_status == LIFT_TOP_CONTROLLED)
            m_initial_roller.set_desired_velocity(200);
    }
    else{
        m_left_intake.set_desired_velocity(0);
        m_right_intake.set_desired_velocity(0);
        m_intake_status = INTAKE_STATIONARY;
    }
}

void Manipulator::task(){
    if(m_robot.get_robot_state() == ROBOT_DRIVER_CONTROL){
        driver_control();
    }
    else if(m_robot.get_robot_state() == ROBOT_AUTONOMOUS){
        autonomous();
    }
    else if(m_robot.get_robot_state() == ROBOT_INITIALIZATION){
        initialize();
    }
}

void Manipulator::define_GUI(){
  GUI::Screen& l_main = GUI::Screen::create_screen("Manipulator");
  l_main.create_rectangle(0, 0, 480, 40, GUI_STYLES::white_text);
  l_main.create_label(200, 10, GUI_STYLES::red_text, "Manipulator");

//   l_main.create_label(20, 50, GUI_STYLES::white_text, "Desired Velocity: %d", m_desired_velocity);
//   l_main.create_label(20, 80, GUI_STYLES::white_text, "Actual Velocity: %d", (std::function<int()>)std::bind(&Motor::get_actual_velocity, this));
//   l_main.create_label(20, 110, GUI_STYLES::white_text, "Position: %d Deg", (std::function<int()>)std::bind(&Motor::get_postion, this));

//   l_main.create_label(260, 50, GUI_STYLES::white_text, "Desired Voltage: %d", m_desired_voltage);
//   l_main.create_label(260, 80, GUI_STYLES::white_text, "Actual Voltage: %d", (std::function<int()>)std::bind(&Motor::get_actual_voltage, this));
//   l_main.create_label(260, 110, GUI_STYLES::white_text, "Temperature: %d C", (std::function<int()>)std::bind(&Motor::get_temperature, this));

  GUI::Button& btn1 = l_main.create_button("Go Back", 160, 200, 150, 20);
  btn1.add_connected_screen("Home");
}