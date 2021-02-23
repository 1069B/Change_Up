#include "robot/robot_class.hpp"

#include "robot/devices/data_storage_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/devices/controller_class.hpp"

#include "robot/sensors/rotation_class.hpp"
#include "robot/sensors/distance_class.hpp"
#include "robot/sensors/optical_class.hpp"
#include "robot/sensors/digital_class.hpp"
#include "robot/sensors/analog_class.hpp"

#include "robot/graphical_interface/screen_class.hpp"
#include "robot/graphical_interface/button_class.hpp"

#include "robot/subsystems/holonomic_class.hpp"
#include "robot/subsystems/manipulator.hpp"
#include "robot/subsystems/autonomous_class.hpp"

Robot::Robot():m_holonomic(*new Holonomic(*this)),
m_manipulator(*new Manipulator(*this)),
m_settings(*new Data_Storing("Settings.xml", "Robot", "1069B")),
m_main_controller(*new CONTROLLER::Controller(pros::E_CONTROLLER_MASTER)),
m_partner_controller(*new CONTROLLER::Controller(pros::E_CONTROLLER_PARTNER)),
m_autonomous(*new Autonomous(*this)){
	m_recall_settings = m_settings.initialize_bool("Recall_Settings", false);
	defineStyles();
}

void Robot::check_robot_status(){
	if (pros::competition::is_connected()){
		if (pros::competition::is_disabled()){
			m_robot_state = ROBOT_DISABLED;
		}
		else{
			if(pros::competition::is_autonomous()){
				m_robot_state = ROBOT_AUTONOMOUS;
			}
			else{
				m_robot_state = ROBOT_DRIVER_CONTROL;
			}
		}
	}
	else{
		m_robot_state = ROBOT_DRIVER_CONTROL;
	}
}

Motor &Robot::add_motor(std::string const p_name, short const p_port, pros::motor_gearset_e_t const p_gearset, pros::motor_brake_mode_e_t const p_brake, bool const p_reversed){
	for (auto x : m_motor_list){
		if (x->get_name() == p_name)
			return *x;
	}

	Motor *l_new_motor{new Motor(*this, p_name, p_port, p_gearset, p_brake, p_reversed)};
	m_motor_list.push_back(l_new_motor);
	l_new_motor->define_GUI();
	return *l_new_motor;
}

SENSOR::Distance &Robot::add_distance(std::string const p_name, short const p_port){
	for (auto x : m_distance_list){
		if (x->get_name() == p_name)
			return *x;
	}

	SENSOR::Distance *l_new_distance{new SENSOR::Distance(*this, p_name, p_port)};
	m_distance_list.push_back(l_new_distance);
	return *l_new_distance;
}

SENSOR::Rotation &Robot::add_rotation(std::string const p_name, short const p_port, bool const p_reversed, int const p_position_offset){
	for (auto x : m_rotation_list){
		if (x->get_name() == p_name)
			return *x;
	}

	SENSOR::Rotation *l_new_rotation{new SENSOR::Rotation(*this, p_name, p_port, p_reversed, p_position_offset)};
	m_rotation_list.push_back(l_new_rotation);
	return *l_new_rotation;
}

SENSOR::Optical &Robot::add_optical(std::string const p_name, short const p_port, short const p_pwm_value){
	for (auto x : m_optical_list){
		if (x->get_name() == p_name)
			return *x;
	}

	SENSOR::Optical *l_new_optical{new SENSOR::Optical(*this, p_name, p_port, p_pwm_value)};
	m_optical_list.push_back(l_new_optical);
	return *l_new_optical;
}

SENSOR::Digital &Robot::add_digital(std::string const p_name, short const p_port){
	for (auto x : m_digital_list){
		if (x->get_name() == p_name)
			return *x;
	}

	SENSOR::Digital *l_new_digital{new SENSOR::Digital(*this, p_name, p_port)};
	m_digital_list.push_back(l_new_digital);
	return *l_new_digital;
}

SENSOR::Analog_Pair &Robot::add_analog_pair(std::string const p_name, short const p_expander_port, short const p_first_port, short const p_second_port, double p_lower_bound, double p_upper_bound){
	for (auto x : m_analog_pair_list){
		if (x->get_name() == p_name)
			return *x;
	}

	SENSOR::Analog_Pair *l_new_analog_pair{new SENSOR::Analog_Pair(*this, p_name, p_expander_port, p_first_port, p_second_port, p_lower_bound, p_upper_bound)};
	m_analog_pair_list.push_back(l_new_analog_pair);
	return *l_new_analog_pair;
}

Motor &Robot::find_motor(std::string const p_name){
	for (auto x : m_motor_list){
		if (x->get_name() == p_name)
			return *x;
	}
	return *new Motor(*this, "Default", 1, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false);
}

void Robot::initialize(){
	m_manipulator.initialize();
	//TODO: ADD HOLONOMIC initialize

	define_autonomous_routines();
	defineGUI();
}

void Robot::task(){
	check_robot_status();
	GUI::Screen::task();

	if (m_robot_state == ROBOT_DRIVER_CONTROL)
	{
		m_holonomic.task();
		m_manipulator.task();
	}
	else if (m_robot_state == ROBOT_AUTONOMOUS)
	{
		m_autonomous.task();
		m_holonomic.task();
		m_manipulator.task();
	}
}

void Robot::defineGUI(){
	GUI::Screen::initialize(*this);
	m_manipulator.define_GUI();

	GUI::Screen &l_home = GUI::Screen::find_screen("Home");
	// l_home.create_label(20, 20, GUI_STYLES::white_text, "Intake Sensor Hue %d", );
	// l_home.create_label(20, 20, GUI_STYLES::white_text, "Intake Sensor Hue %d", );
	// l_home.create_label(20, 20, GUI_STYLES::white_text, "Hello Corey");
	// l_home.create_label(20, 20, GUI_STYLES::white_text, "Hello Corey");

	l_home.create_label(20, 20, GUI_STYLES::white_text, "Hello Corey");
	l_home.create_rectangle(20, 50, 460, 10, GUI_STYLES::red_button_released);
	GUI::Button &btn1 = l_home.create_button("Manipulator", 100, 100, 100, 50, GUI_STYLES::blue_button_released, GUI_STYLES::blue_button_pressed);
	btn1.add_connected_screen("Manipulator");

	GUI::Screen &l_disconnected = GUI::Screen::find_screen("Disconnected");
	l_disconnected.create_label(20, 20, GUI_STYLES::white_text, "Device not Connected");
	GUI::Button &btn2 = l_disconnected.create_button("Home", 100, 100, 100, 50, GUI_STYLES::blue_button_released, GUI_STYLES::blue_button_pressed);
	btn2.add_connected_screen("Home");

	GUI::Screen &l_settings = GUI::Screen::create_screen("Settings");
	l_settings.create_label(20, 20, GUI_STYLES::white_text, "It Worked!");
}
