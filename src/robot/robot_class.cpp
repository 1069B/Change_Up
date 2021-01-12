#include "robot/robot_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/sensors/rotation_class.hpp"
#include "robot/sensors/distance_class.hpp"
#include "robot/sensors/optical_class.hpp"
#include "robot/sensors/digital_class.hpp"
#include "robot/graphical_interface/button_class.hpp"


Robot::Robot(){
  m_recall_settings = m_settings.initialize_bool("Recall_Settings", false);
  defineStyles();
}

Motor& Robot::add_motor(std::string const p_name, short const p_port, pros::motor_gearset_e_t const p_gearset, pros::motor_brake_mode_e_t const p_brake, bool const p_reversed){
  for(int x = 0; x < m_motor_list.size(); x++){
    if(m_motor_list.at(x)->get_name() == p_name)
      return *m_motor_list.at(x);
  }

  Motor* l_new_motor{new Motor(*this, p_name, p_port, p_gearset, p_brake, p_reversed)};
  m_motor_list.push_back(l_new_motor);
  l_new_motor->define_GUI();
  return *l_new_motor;
}

SENSOR::Distance& Robot::add_distance(std::string const p_name, short const p_port){
  for(int x = 0; x < m_distance_list.size(); x++){
    if(m_distance_list.at(x)->get_name() == p_name)
      return *m_distance_list.at(x);
  }

  SENSOR::Distance* l_new_distance{new SENSOR::Distance(*this, p_name, p_port)};
  m_distance_list.push_back(l_new_distance);
  return *l_new_distance;
}

SENSOR::Rotation& Robot::add_rotation(std::string const p_name, short const p_port, bool const p_reversed, int const p_position_offset){
  for(int x = 0; x < m_rotation_list.size(); x++){
    if(m_rotation_list.at(x)->get_name() == p_name)
      return *m_rotation_list.at(x);
  }

  SENSOR::Rotation* l_new_rotation{new SENSOR::Rotation(*this, p_name, p_port, p_reversed, p_position_offset)};
  m_rotation_list.push_back(l_new_rotation);
  return *l_new_rotation;
}

SENSOR::Optical& Robot::add_optical(std::string const p_name, short const p_port, short const p_pwm_value){
  for(int x = 0; x < m_optical_list.size(); x++){
    if(m_optical_list.at(x)->get_name() == p_name)
      return *m_optical_list.at(x);
  }

  SENSOR::Optical* l_new_optical{new SENSOR::Optical(*this, p_name, p_port, p_pwm_value)};
  m_optical_list.push_back(l_new_optical);
  return *l_new_optical;
}

SENSOR::Digital& Robot::add_digital(std::string const p_name, short const p_port){
  for(int x = 0; x < m_digital_list.size(); x++){
    if(m_digital_list.at(x)->get_name() == p_name)
      return *m_digital_list.at(x);
  }

  SENSOR::Digital* l_new_digital{new SENSOR::Digital(*this, p_name, p_port)};
  m_digital_list.push_back(l_new_digital);
  return *l_new_digital;
}

void Robot::task(){
  GUI::Screen::task();
}

void Robot::defineGUI(){
  GUI::Screen::initialize(*this);

  GUI::Screen& l_home = GUI::Screen::find_screen("Home");
  l_home.create_label(20, 20, GUI_STYLES::white_text, "Hello Corey");
  l_home.create_rectanlge(20, 50, 460, 10, GUI_STYLES::red_button_released);
  GUI::Button& btn1 = l_home.create_button("Motor 1", 100, 100, 100, 50, GUI_STYLES::blue_button_released, GUI_STYLES::blue_button_pressed);
  btn1.add_connected_screen("Base_Front_Left");

  GUI::Screen& l_disconnected = GUI::Screen::find_screen("Disconnected");
  l_disconnected.create_label(20, 20, GUI_STYLES::white_text, "Device not Connected");
  GUI::Button& btn2 = l_disconnected.create_button("Home", 100, 100, 100, 50, GUI_STYLES::blue_button_released, GUI_STYLES::blue_button_pressed);
  btn2.add_connected_screen("Home");

  GUI::Screen& l_settings = GUI::Screen::create_screen("Settings");
  l_settings.create_label(20, 20, GUI_STYLES::white_text, "It Worked!");


}
