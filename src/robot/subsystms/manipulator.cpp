#include "robot/robot_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/devices/controller_class.hpp"
#include "robot/devices/timer_class.hpp"
#include "robot/subsystems/manipulator.hpp"
#include "robot/robot_class.hpp"


#include "robot/graphical_interface/screen_class.hpp"
#include "robot/graphical_interface/button_class.hpp"
#include "robot/graphical_interface/switch_class.hpp"
#include "robot/graphical_interface/roller_class.hpp"

Manipulator::Manipulator(Robot& p_robot):
m_robot(p_robot),
m_timer(*new Timer()),
m_left_intake(m_robot.add_motor("Left Intake", 12, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_COAST, false)),
m_right_intake(m_robot.add_motor("Right Intake", 19, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_COAST, true)),
m_initial_roller(m_robot.add_motor("Initial Rollers", 9, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_BRAKE, true)),
m_secondary_roller(m_robot.add_motor("Second Rollers", 10, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_COAST, true)){
    	
}

void Manipulator::initialize(){

}

void Manipulator::autonomous(){
    int l_rgb = pros::c::optical_get_hue(20);

    if(m_intake_status != INTAKE_INTAKING && ((12 < l_rgb && l_rgb < 32) || (190 < l_rgb && l_rgb < 210))){
        m_intake_status = INTAKE_INTAKING;
    }
    else if(m_intake_status == INTAKE_INTAKING && !((12 < l_rgb && l_rgb < 32) || (190 < l_rgb && l_rgb < 210))){
        m_intake_status = INTAKE_OPENING;
        m_timer.set_flag_delay(500);
    }
    else if(m_intake_status == INTAKE_OPENING && m_timer.get_preform_action()){
        m_intake_status = INTAKE_STATIONARY;
    }
    else{
        m_intake_status = INTAKE_STATIONARY;
    }
}

void Manipulator::driver_control(){
    int l_rgb = pros::c::optical_get_hue(20);
    int l_lower_detection;
    int l_upper_detection;

    if(m_robot.get_alliance() == ROBOT_SKILLS){
        l_lower_detection = 12;
        l_upper_detection = 78;
    }
    else if(m_robot.get_alliance() == ROBOT_RED){
        l_lower_detection = 12;
        l_upper_detection = 78;
    }
    else if(m_robot.get_alliance() == ROBOT_BLUE){
        l_lower_detection = 190;
        l_upper_detection = 210;
    }


    if(m_robot.get_partner_controller().Axis2.get_percent() < -0.10 || 0.10 < m_robot.get_partner_controller().Axis2.get_percent()){
        m_lift_status = LIFT_USER_BASED;
    }
    else if(m_robot.get_partner_controller().ButtonR1.get_state()){
        m_lift_status = LIFT_SCORING;
    }
    else if(m_robot.get_partner_controller().ButtonR2.get_state()){
        m_lift_status = LIFT_EJECTING;
    }
    else{
        m_lift_status = LIFT_STATIONARY;
    }

    if(m_robot.get_partner_controller().Axis3.get_percent() < -0.10 || 0.10 < m_robot.get_partner_controller().Axis3.get_percent()){
        m_intake_status = INTAKE_USER_BASED;
    }
    else if(m_robot.get_partner_controller().ButtonL1.get_state()){
        m_intake_status = INTAKE_INTAKING;
        if(!(m_lift_status == LIFT_SCORING || m_lift_status == LIFT_EJECTING)){
            m_lift_status = LIFT_INTAKING;
        }
    }
    else if(m_robot.get_partner_controller().ButtonL2.get_state()){
        m_intake_status = INTAKE_OPENING;
    }
    else if(l_lower_detection < l_rgb && l_rgb < l_upper_detection){
        m_intake_status = INTAKE_AUTO_INTAKE;

        if(!(m_lift_status == LIFT_SCORING || m_lift_status == LIFT_EJECTING)){
            m_lift_status = LIFT_INTAKING;
        }
    }
    else if(m_intake_status == INTAKE_AUTO_INTAKE && !(l_lower_detection < l_rgb && l_rgb < l_upper_detection)){
        m_intake_status = INTAKE_AUTO_OPEN;
        m_timer.set_flag_delay(500);
    }
    else if(m_intake_status == INTAKE_AUTO_OPEN && m_timer.get_preform_action()){
        m_intake_status = INTAKE_STATIONARY;
    }
    else if(m_intake_status == INTAKE_AUTO_OPEN){
        if(!(m_lift_status == LIFT_SCORING || m_lift_status == LIFT_EJECTING)){
            m_lift_status = LIFT_INTAKING;
        }
    }
    else if(m_intake_status != INTAKE_AUTO_OPEN){
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

    switch(m_intake_status){
        case INTAKE_INTAKING: 
            m_left_intake.set_desired_velocity(600);
            m_right_intake.set_desired_velocity(600);
            break;

        case INTAKE_AUTO_INTAKE: 
            m_left_intake.set_desired_velocity(600);
            m_right_intake.set_desired_velocity(600);
            break;

        case INTAKE_OPENING: 
            m_left_intake.set_desired_velocity(-300);
            m_right_intake.set_desired_velocity(-300);
            break;

        case INTAKE_AUTO_OPEN: 
            m_left_intake.set_desired_velocity(-300);
            m_right_intake.set_desired_velocity(-300);
            break;

        case INTAKE_STATIONARY: 
            m_left_intake.set_desired_velocity(0);
            m_right_intake.set_desired_velocity(0);
            break;

        case INTAKE_USER_BASED: 
            m_left_intake.set_desired_velocity(m_robot.get_partner_controller().Axis3.get_percent() * 600);
            m_right_intake.set_desired_velocity(m_robot.get_partner_controller().Axis3.get_percent() * 600);
            break;
    }

    switch(m_lift_status){
        case LIFT_INTAKING:
            m_initial_roller.set_desired_velocity(200);
			m_secondary_roller.set_desired_velocity(0);
            break;
        case LIFT_SCORING: 
            m_initial_roller.set_desired_velocity(600);
			m_secondary_roller.set_desired_velocity(600);
            break;

        case LIFT_EJECTING: 
            m_initial_roller.set_desired_velocity(200);
			m_secondary_roller.set_desired_velocity(-600);// TODO: Change automatic sorting
            break;

        case LIFT_STATIONARY: 
            m_initial_roller.set_desired_velocity(0);
			m_secondary_roller.set_desired_velocity(0);
            break;

        case LIFT_USER_BASED: 
            m_initial_roller.set_desired_velocity(fabs(m_robot.get_partner_controller().Axis2.get_percent() * 600));
			m_secondary_roller.set_desired_velocity(m_robot.get_partner_controller().Axis2.get_percent() * 600);
            break;
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