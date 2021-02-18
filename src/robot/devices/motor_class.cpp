#include "robot/devices/motor_class.hpp"

#include "robot/robot_class.hpp"

#include "robot/devices/data_storage_class.hpp"

#include "robot/graphical_interface/screen_class.hpp"
#include "robot/graphical_interface/button_class.hpp"
#include "robot/graphical_interface/switch_class.hpp"
#include "robot/graphical_interface/roller_class.hpp"

Motor::Motor(Robot &p_robot, std::string const p_name, int const p_port, pros::motor_gearset_e_t const p_motor_gearset, pros::motor_brake_mode_e_t const p_motor_brake, bool const p_reversed):
m_robot(p_robot),
m_settings(*new Data_Storing("Settings.xml", "Motors", p_name)){
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

  m_port_temp = m_port;
  m_reversed_temp = m_reversed;
  m_brake_mode_temp = (int)m_brake_mode;
  m_gearset_mode_temp = (int)m_motor_gearset;

  update();
}

/* Setter Function */
void Motor::set_port(int const p_port){
  m_port = p_port;
  m_port_temp = m_port;
  update();
}

void Motor::set_reversed(bool const p_reversed){
  m_reversed = p_reversed;
  m_reversed_temp = m_reversed;
  update();
}

void Motor::set_brake_mode(pros::motor_brake_mode_e_t const p_brake_mode){
  m_brake_mode = p_brake_mode;
  m_brake_mode_temp = (int)m_brake_mode;
  update();
}

void Motor::set_motor_gearset(pros::motor_gearset_e_t const p_motor_gearset){
  m_motor_gearset = p_motor_gearset;
  m_gearset_mode_temp = (int)m_motor_gearset;
  update();
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

void Motor::operator=(int p_velocity){
  set_desired_velocity(p_velocity);
}
void Motor::operator=(double p_velocity){
  set_desired_velocity((int)p_velocity);
}

int Motor::update(){
  m_brake_mode = (pros::motor_brake_mode_e_t)m_brake_mode_temp;
  m_motor_gearset = (pros::motor_gearset_e_t)m_gearset_mode_temp;

  switch(m_brake_mode_temp) {
    case 0:
      m_brake_mode_string = "Coast";
      break;
    case 1:
      m_brake_mode_string = "Brake";
      break;
    case 2:
      m_brake_mode_string = "Hold";
  }

  switch(m_gearset_mode_temp) {
    case 0:
      m_gearset_mode_string = "100 RPM";
      break;
    case 1:
      m_gearset_mode_string = "200 RPM";
      break;
    case 2:
      m_gearset_mode_string = "600 RPM";
  }

  m_port = m_port_temp;
  m_reversed = m_reversed_temp;

  m_settings.store_int("Port", m_port);
  m_settings.store_int("Brake", m_brake_mode);
  m_settings.store_int("Gearset", m_motor_gearset);
  m_settings.store_bool("Reversed", m_reversed);

  pros::c::motor_set_gearing(m_port, m_motor_gearset);
  pros::c::motor_set_brake_mode(m_port, m_brake_mode);
  pros::c::motor_set_reversed(m_port, m_reversed);
  pros::c::motor_set_encoder_units(m_port, pros::E_MOTOR_ENCODER_ROTATIONS);
  return 0;
}

void Motor::define_GUI(){
  GUI::Screen& l_main = GUI::Screen::create_screen(m_name);
  l_main.create_rectangle(0, 0, 480, 40, GUI_STYLES::white_text);
  l_main.create_label(200, 10, GUI_STYLES::red_text, m_name);

  l_main.create_label(20, 50, GUI_STYLES::white_text, "Desired Velocity: %d", m_desired_velocity);
  l_main.create_label(20, 80, GUI_STYLES::white_text, "Actual Velocity: %d", (std::function<int()>)std::bind(&Motor::get_actual_velocity, this));
  l_main.create_label(20, 110, GUI_STYLES::white_text, "Position: %d Deg", (std::function<int()>)std::bind(&Motor::get_postion, this));

  l_main.create_label(260, 50, GUI_STYLES::white_text, "Desired Voltage: %d", m_desired_voltage);
  l_main.create_label(260, 80, GUI_STYLES::white_text, "Actual Voltage: %d", (std::function<int()>)std::bind(&Motor::get_actual_voltage, this));
  l_main.create_label(260, 110, GUI_STYLES::white_text, "Temperature: %d C", (std::function<int()>)std::bind(&Motor::get_temperature, this));

  GUI::Button& btn1 = l_main.create_button("Go Back", 160, 200, 150, 20);
  btn1.add_connected_screen("Home");

  GUI::Button& btn2 = l_main.create_button(SYMBOL_SETTINGS, 440, 5, 30, 30);
  btn2.add_connected_screen(m_name + " Settings");

  //l_main.add_relationship((std::function<bool()>)std::bind(&Motor::get_connected, this), "Disconnected", true);


  GUI::Screen& l_settings = GUI::Screen::create_screen(m_name + " Settings");
  l_settings.create_rectangle(0, 0, 480, 40, GUI_STYLES::white_text);
  l_settings.create_label(0, 10, GUI_STYLES::red_text, m_name + " Settings", LV_ALIGN_IN_TOP_MID);


  l_settings.create_label(20, 70, GUI_STYLES::white_text, "Port: %d", m_port, LV_ALIGN_IN_TOP_LEFT);

  std::vector<std::string>* l_port_string = new std::vector<std::string>{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
  std::vector<int>* l_port_int = new std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  GUI::Roller& l_port_roller = l_settings.create_roller(100, 50, 40, *l_port_string, m_port-1, GUI_STYLES::roller_background, GUI_STYLES::roller_selected);
  l_port_roller.add_connected_int(m_port_temp, *l_port_int);

  l_settings.create_label(20, 130, GUI_STYLES::white_text, "Reversed: %d", m_reversed);
  GUI::Switch& l_reversed = l_settings.create_switch(50, 160, m_reversed, GUI_STYLES::switch_background, GUI_STYLES::switch_inactive, GUI_STYLES::switch_on, GUI_STYLES::switch_off);
  l_reversed.add_connected_bool(m_reversed_temp);


  l_settings.create_label(240, 70, GUI_STYLES::white_text, "Brake Mode:\n     %d", m_brake_mode_string);

  std::vector<std::string>* l_brake_string = new std::vector<std::string>{"COAST", "BRAKE", "HOLD"};
  std::vector<int>* l_brake_int = new std::vector<int>{0, 1, 2};
  GUI::Roller& l_brake_roller = l_settings.create_roller(375, 50, 100, *l_brake_string, (int)m_brake_mode, GUI_STYLES::roller_background, GUI_STYLES::roller_selected);
  l_brake_roller.add_connected_int(m_brake_mode_temp, *l_brake_int);


  l_settings.create_label(240, 130, GUI_STYLES::white_text, "Motor Gearset:\n     %d", m_gearset_mode_string);

  std::vector<std::string>* l_gearset_string = new std::vector<std::string>{"100 RPM", "200 RPM", "600 RPM"};
  std::vector<int>* l_gearset_int = new std::vector<int>{0, 1, 2};
  GUI::Roller& l_list_gearset = l_settings.create_roller(375, 120, 100, *l_gearset_string, (int)m_motor_gearset, GUI_STYLES::roller_background, GUI_STYLES::roller_selected);
  l_list_gearset.add_connected_int(m_gearset_mode_temp, *l_gearset_int);

  GUI::Button& btn_update = l_settings.create_button("Update", 100, 200, 150, 20);
  btn_update.add_connected_function((std::function<int()>)std::bind(&Motor::update, this));

  GUI::Button& btn3 = l_settings.create_button("Go Back", 300, 200, 150, 20);
  btn3.add_connected_screen(m_name);
}
