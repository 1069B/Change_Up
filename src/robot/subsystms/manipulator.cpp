#include "robot/robot_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/devices/controller_class.hpp"
#include "robot/devices/timer_class.hpp"

#include "robot/subsystems/manipulator.hpp"

#include "robot/sensors/optical_class.hpp"
#include "robot/sensors/distance_class.hpp"
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
m_sorting_sensor(m_robot.add_optical("Sorting Sensor", 2)),
m_scoring_sensor(m_robot.add_distance("Scoring Sensor", 14)),
m_left_intake_sensor(m_robot.add_digital("Intake Left", 2)),
m_right_intake_sensor(m_robot.add_digital("Intake Right", 1))
{
    	
}

void Manipulator::initialize(){
    if(m_robot.get_alliance() == ROBOT_SKILLS || m_robot.get_alliance() == ROBOT_RED){
        m_intake_sensor.set_signature_1(12, 75);
        m_intake_sensor.set_signature_2(180, 220);

        m_sorting_sensor.set_signature_1(0, 20);// Scoring
        m_sorting_sensor.set_signature_2(206, 226);// Eject
    }
    else if(m_robot.get_alliance() == ROBOT_BLUE){
        m_intake_sensor.set_signature_1(190, 210);

        m_sorting_sensor.set_signature_1(206, 226);// Scoring
        m_sorting_sensor.set_signature_2(0, 20);// Eject
    }
}

void Manipulator::set_intake_velocities(int const p_left_velocity, int const p_right_velocity){
    m_left_intake = p_left_velocity;
    m_right_intake = p_right_velocity;
}

void Manipulator::intake_auto_grabbing(){
    if(m_ball_positions.m_intakes == BALL_DESIRED){
        if(m_ball_positions.m_scoreing == BALL_DESIRED && (m_ball_positions.m_sorting == BALL_DESIRED || m_ball_positions.m_tongue == BALL_DESIRED)){
            set_intake_velocities(0, 0);
            m_initial_roller.set_desired_velocity(0);
        }
        else{
            set_intake_velocities(600, 600);
            m_initial_roller.set_desired_velocity(200);
            m_intake_status = INTAKE_AUTO_INTAKE;
        }
    }
    else if(m_ball_positions.m_intakes != BALL_DESIRED && m_intake_status == INTAKE_AUTO_INTAKE){
        m_ball_positions.m_intakes = BALL_NONE;
        m_ball_positions.m_tongue = BALL_DESIRED;

        //Reverse Intakes
        m_intake_status = INTAKE_AUTO_OPEN;
        set_intake_velocities(-300, -300);
        m_initial_roller.set_desired_velocity(0);

        m_intake_timer.set_flag_delay(500);
    }
    else if(m_intake_status == INTAKE_AUTO_OPEN && m_intake_timer.get_preform_action()){
        set_intake_velocities(0, 0);
        m_intake_status = INTAKE_STATIONARY;
    }

}
void Manipulator::intake_scoring(){

}
void Manipulator::intake_store(){
    if(m_left_intake_sensor.get_value() == 0)
        m_left_intake.set_desired_velocity(-500);
    else
        m_left_intake.set_desired_velocity(0);

    if(m_right_intake_sensor.get_value() == 0)
        m_right_intake.set_desired_velocity(-500);
    else
        m_right_intake.set_desired_velocity(0);
}

void Manipulator::manipulator_sorting(){
     /*Manipulator Ball Position*/
    if(m_ball_positions.m_scoreing != BALL_DESIRED){
        m_initial_roller.set_desired_velocity(200);
        if(m_ball_positions.m_tongue != BALL_NONE){// Moves the ball to sorting
            m_secondary_roller.set_desired_velocity(600);
            m_ball_positions.m_tongue = BALL_NONE;
        }
        else if(m_ball_positions.m_sorting == BALL_DESIRED){// Lifts the Ball up to scoring
            m_secondary_roller.set_desired_velocity(600);
        }
        else if(m_ball_positions.m_sorting == BALL_OPPOSING){// Sorts the ball out
            m_secondary_roller.set_desired_velocity(-600);
        }
    }
    else if(m_ball_positions.m_scoreing == BALL_DESIRED){
        m_secondary_roller.set_desired_velocity(0);
        if(m_ball_positions.m_tongue != BALL_NONE){
            m_initial_roller.set_desired_velocity(0);
        }
        else if(m_ball_positions.m_sorting == BALL_DESIRED){// Ball in top and desired
            m_initial_roller.set_desired_velocity(-100);
            m_ball_positions.m_tongue = BALL_DESIRED;
        }
        else if(m_ball_positions.m_sorting == BALL_OPPOSING){// Ball ejection
            m_initial_roller.set_desired_velocity(200);
        }
        else if(m_ball_positions.m_tongue == BALL_NONE && m_ball_positions.m_sorting == BALL_NONE && m_ball_positions.m_intakes == BALL_NONE){
            m_initial_roller.set_desired_velocity(0);
        }
    }
}
void Manipulator::manipulator_scoring(){
    if(m_shooting_status == LIFT_WAITING){
        m_initial_roller.set_desired_velocity(0);
        m_secondary_roller.set_desired_velocity(600);
        m_shooting_status = LIFT_SCORING;
        m_lift_timer.set_flag_delay(1500);
    }
    else if(m_shooting_status == LIFT_SCORING && m_lift_timer.get_preform_action()){
        m_initial_roller.set_desired_velocity(0);
        m_secondary_roller.set_desired_velocity(0);
        m_shooting_status = LIFT_STATIONARY;
    }
}

void Manipulator::autonomous(){
    // if(m_mode == MANIPULATOR_FEILD)
    //     autonomous_feild();
    // else if(m_mode == MANIPULATOR_SCORE)
    //     autonomous_score();
}

void Manipulator::driver_control(){
    if(m_shooting_status != LIFT_SCORING && m_robot.get_partner_controller().ButtonR1.get_state()){// If button is pressed than scoring is active
        m_shooting_status = LIFT_WAITING;
        manipulator_scoring();
    }
    else if(m_shooting_status == LIFT_SCORING){
        manipulator_scoring();
    }
    else if(outside_range(m_robot.get_partner_controller().Axis2.get_percent(), 0.1)){// User input
        m_initial_roller = m_robot.get_partner_controller().Axis2.get_percent() * 200;
		m_secondary_roller = m_robot.get_partner_controller().Axis2.get_percent() * 600;
    }
    else{// Run auto code for sorting
        manipulator_sorting();
    }

    if(outside_range(m_robot.get_partner_controller().Axis3.get_percent(), 0.1)){
        set_intake_velocities(m_robot.get_partner_controller().Axis3.get_percent() * 600);
    }
    else if(m_robot.get_partner_controller().ButtonL1.get_state()){
        set_intake_velocities(600);
    }
    else if(m_robot.get_partner_controller().ButtonL2.get_state()){
        intake_store();
    }
    else{
        intake_auto_grabbing();
    }
}

void Manipulator::task(){
    /* Detects Current Ball Position */
    if(m_scoring_sensor.get_distance() <= 20)
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
        m_ball_positions.m_intakes = BALL_DESIRED;
    else if(m_intake_sensor.is_signature_2())
        m_ball_positions.m_intakes = BALL_OPPOSING;
    else
        m_ball_positions.m_intakes = BALL_NONE;

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

  //l_main.create_label(20, 20, GUI_STYLES::white_text, "Intake Sensor Hue %d", (std::function<int()>)std::bind(&Optical::get_hue, this));
  //l_main.create_label(20, 20, GUI_STYLES::white_text, "Intake Sensor Hue %d", (std::function<int()>)std::bind(&Optical::get_actual_velocity, this));

//   l_main.create_label(20, 50, GUI_STYLES::white_text, "Desired Velocity: %d", m_desired_velocity);
//   l_main.create_label(20, 80, GUI_STYLES::white_text, "Actual Velocity: %d", (std::function<int()>)std::bind(&Motor::get_actual_velocity, this));
//   l_main.create_label(20, 110, GUI_STYLES::white_text, "Position: %d Deg", (std::function<int()>)std::bind(&Motor::get_postion, this));

//   l_main.create_label(260, 50, GUI_STYLES::white_text, "Desired Voltage: %d", m_desired_voltage);
//   l_main.create_label(260, 80, GUI_STYLES::white_text, "Actual Voltage: %d", (std::function<int()>)std::bind(&Motor::get_actual_voltage, this));
//   l_main.create_label(260, 110, GUI_STYLES::white_text, "Temperature: %d C", (std::function<int()>)std::bind(&Motor::get_temperature, this));

  GUI::Button& btn1 = l_main.create_button("Go Back", 160, 200, 150, 20);
  btn1.add_connected_screen("Home");
}