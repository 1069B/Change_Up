#include "robot/devices/motor_class.hpp"
#include "robot/robot_class.hpp"
#include "robot/graphical_interface/button_class.hpp"
#include "robot/graphical_interface/switch_class.hpp"

Motor::Motor(Robot &p_robot, std::string const p_name, short const p_port, pros::motor_gearset_e_t const p_motor_gearset, pros::motor_brake_mode_e_t const p_motor_brake, bool const p_reversed):
m_robot(p_robot),
m_settings("Settings.xml", "Motors", p_name){
  if(m_robot.get_recall_settings()){
    m_name = p_name;
    m_port = m_settings.initialize_int("Port", p_port);
    m_motor_gearset = (pros::motor_gearset_e_t)m_settings.initialize_int("Gearset", (int)p_motor_gearset);
    m_brake_mode = (pros::motor_brake_mode_e_t)m_settings.initialize_int("Brake", (int)p_motor_brake);
    m_reversed = m_settings.initialize_bool("Reversed", p_reversed);
  }
  else{
    m_name = p_name;
    m_port = p_port;
    m_motor_gearset = p_motor_gearset;
    m_reversed = p_reversed;
  }

  pros::c::motor_set_gearing(m_port, m_motor_gearset);
  pros::c::motor_set_brake_mode(m_port, m_brake_mode);
  pros::c::motor_set_reversed(m_port, m_reversed);
  pros::c::motor_set_encoder_units(m_port, pros::E_MOTOR_ENCODER_ROTATIONS);
}

/* Setter Function */
void Motor::set_port(short const p_port){
  m_port = p_port;
  m_settings.store_int("Port", m_port);
}

void Motor::set_reversed(bool const p_reversed){
  m_reversed = p_reversed;
  m_settings.store_bool("Reversed", m_reversed);
}

void Motor::set_brake_mode(pros::motor_brake_mode_e_t const p_brake_mode){
  m_brake_mode = p_brake_mode;
  m_settings.store_int("Brake", m_brake_mode);
}

void Motor::set_motor_gearset(pros::motor_gearset_e_t const p_motor_gearset){
  m_motor_gearset = p_motor_gearset;
  m_settings.store_int("Gearset", m_motor_gearset);
  pros::c::motor_set_gearing(m_port, m_motor_gearset);
}

void Motor::set_desired_velocity(int const p_desired_velocity){
  m_desired_velocity = p_desired_velocity;
  m_mode = MOTOR_VELOCITY_DEPENDENT;
  m_desired_voltage = 0;
  pros::c::motor_move_velocity(m_port, m_desired_velocity);
}

void Motor::set_desired_voltage(int const p_desired_voltage){
  m_desired_voltage = p_desired_voltage;
  m_mode = MOTOR_VOLTAGE_DEPENDENT;
  m_desired_velocity = 0;
  pros::c::motor_move_voltage(m_port, m_desired_voltage);
}

void Motor::define_GUI(){
  GUI::Screen& l_main = GUI::Screen::create_screen(m_name);
  l_main.create_rectanlge(0, 0, 480, 40, GUI_STYLES::white_text);
  l_main.create_label(200, 10, GUI_STYLES::red_text, m_name);

  l_main.create_label(20, 50, GUI_STYLES::white_text, "Desired Velocity: %d", m_desired_velocity);
  l_main.create_label(20, 80, GUI_STYLES::white_text, "Actual Velocity: %d", (std::function<int()>)std::bind(&Motor::get_actual_velocity, this));
  l_main.create_label(20, 110, GUI_STYLES::white_text, "Position: %d Deg", (std::function<int()>)std::bind(&Motor::get_postion, this));
  l_main.create_label(20, 140, GUI_STYLES::white_text, "Reversed: %d", m_reversed);
  //l_screen.create_label(m_name, 20, 170, GUI_STYLES::white_text, "Motor Gearset: %s", &m_motor_gearset);

  l_main.create_label(260, 50, GUI_STYLES::white_text, "Desired Voltage: %d", m_desired_voltage);
  l_main.create_label(260, 80, GUI_STYLES::white_text, "Actual Voltage: %d", (std::function<int()>)std::bind(&Motor::get_actual_voltage, this));
  l_main.create_label(260, 110, GUI_STYLES::white_text, "Tempature: %d C", (std::function<int()>)std::bind(&Motor::get_tempature, this));
  //l_screen.create_label(m_name, 260, 140, GUI_STYLES::white_text, "Internal PID: %b", m_mode);
  //l_screen.create_label(m_name, 260, 170, GUI_STYLES::white_text, "Brake Mode: %s", &m_brake_mode);

  GUI::Button& btn1 = l_main.create_button("Go Back", 160, 200, 150, 20);
  btn1.add_connected_screen("Home");

  GUI::Button& btn2 = l_main.create_button(SYMBOL_SETTINGS, 440, 5, 30, 30);
  btn2.add_connected_screen(m_name + " Settings");

  l_main.add_relationship((std::function<bool()>)std::bind(&Motor::get_connected, this), "Disconnected", true);


  GUI::Screen& l_settings = GUI::Screen::create_screen(m_name + " Settings");
  l_settings.create_rectanlge(0, 0, 480, 40, GUI_STYLES::white_text);
  l_settings.create_label(0, 10, GUI_STYLES::red_text, m_name + " Settings", LV_ALIGN_IN_TOP_MID);


  std::vector<std::string>* l_string = new std::vector<std::string>{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
  l_settings.create_label(20, 50, GUI_STYLES::white_text, "Port:");
  GUI::List& l_list1 = l_settings.create_list(200, 10, 100, 40, *l_string, 1, &GUI_STYLES::switch_background, &GUI_STYLES::red_button_released, &GUI_STYLES::red_text);

  l_settings.create_label(20, 90, GUI_STYLES::white_text, "Reversed:");
  GUI::Switch& l_reversed = l_settings.create_switch(120, 88, m_reversed, GUI_STYLES::switch_background, GUI_STYLES::switch_inactive, GUI_STYLES::switch_on, GUI_STYLES::switch_off);
  l_reversed.add_connected_bool(m_reversed);

  l_settings.create_label(20, 130, GUI_STYLES::white_text, "Brake Mode:");
  l_settings.create_label(20, 170, GUI_STYLES::white_text, "Motor Gearset:");

  GUI::Button& btn3 = l_settings.create_button("Go Back", 160, 200, 150, 20);
  btn3.add_connected_screen(m_name);
}
