#include "robot/robot_class.hpp"
#include "robot/sensors/rotation_class.hpp"
#include "robot/devices/data_storage_class.hpp"

using namespace SENSOR;

Rotation::Rotation(Robot& p_robot, std::string const p_name, short const p_port, bool const p_reversed, int const p_position_offset):
m_robot(p_robot),
m_settings(*new Data_Storing("Settings.xml", "Sensors", p_name)),
m_average_velocity_vector(10,0){
  if(m_robot.get_recall_settings()){
    m_name = p_name;
    m_port = m_settings.initialize_int("Port", p_port);
    m_reversed = m_settings.initialize_bool("Reversed", p_reversed);
    m_position_offset = m_settings.initialize_int("Position_Offset", p_position_offset);
  }
  else{
    m_name = p_name;
    m_port = p_port;
    m_reversed = p_reversed;
    m_position_offset = p_position_offset;
  }
}

/* Getter Functions */
double Rotation::get_velocity(){
  double l_velocity = (double)pros::c::rotation_get_velocity(m_port)/36000.0;

  std::vector<double> l_velocity_average_vector;
  for(int x = 1; x < m_average_velocity_vector.size(); x++){
    l_velocity_average_vector.push_back(m_average_velocity_vector.at(x));
  }
  l_velocity_average_vector.push_back(l_velocity);
  m_average_velocity_vector = l_velocity_average_vector;
  return l_velocity;
}

double Rotation::get_running_average_velocity(){
  double l_sum = 0;
  for(int x = 0; x < m_average_velocity_vector.size(); x++)
    l_sum += m_average_velocity_vector.at(x);

  return l_sum/(double)m_average_velocity_vector.size();
}

/* Setter Functions */
void Rotation::set_position_offset(int const p_position_offset){
  m_position_offset = p_position_offset;
  m_settings.store_int("Position_Offset", p_position_offset);
}
void Rotation::set_reversed(bool const p_reversed){
  m_reversed = p_reversed;
  m_settings.store_bool("Reversed", p_reversed);
}
void Rotation::set_port(int const p_port){
  m_port = p_port;
  m_settings.store_int("Port", p_port);
}
