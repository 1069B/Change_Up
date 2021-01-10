#include "robot/robot_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/sensors/rotation_class.hpp"
#include "robot/sensors/distance_class.hpp"
#include "robot/sensors/optical_class.hpp"
#include "robot/sensors/digital_class.hpp"


Robot::Robot(){
  m_recall_settings = m_settings.initialize_bool("Recall_Settings", false);
  GUI::Screen::initialize(*this);
  defineGUI();
}

Motor& Robot::add_motor(std::string const p_name, short const p_port, pros::motor_gearset_e_t const p_gearset, pros::motor_brake_mode_e_t const p_brake, bool const p_reversed){
  for(int x = 0; x < m_motor_list.size(); x++){
    if(m_motor_list.at(x)->get_name() == p_name)
      return *m_motor_list.at(x);
  }

  Motor* l_new_motor{new Motor(*this, p_name, p_port, p_gearset, p_brake, p_reversed)};
  m_motor_list.push_back(l_new_motor);
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

void defineGUI(){
  GUI::Screen& l_home = GUI::Screen::find_screen("Home");
  l_home.create_label("Inital", 20, 20, whiteText, "Hello Corey");
}
