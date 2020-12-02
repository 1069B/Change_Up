#include "robot/sensors/inertial_class.hpp"
#include "robot/robot_class.hpp"

using namespace SENSOR;

Inertial::Inertial(Robot &p_robot, std::string const p_name, short const p_port):
m_robot(p_robot),
m_settings("Settings.xml", "Inertial", p_name){
  if(m_robot.get_recall_settings()){
    m_name = p_name;
    m_port = m_settings.initialize_int("Port", p_port);
  }
  else{
    m_name = p_name;
    m_port = p_port;
  }
}

/*  Getting Functions  */
int Inertial::get_pitch(){
  int l_pitch = pros::c::imu_get_pitch(m_port) + m_pitch_offset;

  std::vector<int> l_pitch_vector;
  for(int x = 1; x < m_average_pitch_vector.size(); x++){
    l_pitch_vector.push_back(m_average_pitch_vector.at(x));
  }
  l_pitch_vector.push_back(l_pitch);
  m_average_pitch_vector = l_pitch_vector;
  return l_pitch;
}

int Inertial::get_roll(){
  int l_roll = pros::c::imu_get_roll(m_port) + m_roll_offset;

  std::vector<int> l_roll_vector;
  for(int x = 1; x < m_average_roll_vector.size(); x++){
    l_roll_vector.push_back(m_average_roll_vector.at(x));
  }
  l_roll_vector.push_back(l_roll);
  m_average_roll_vector = l_roll_vector;
  return l_roll;
}

int Inertial::get_yaw(){
  int l_yaw = pros::c::imu_get_yaw(m_port) + m_yaw_offset;

  std::vector<int> l_yaw_vector;
  for(int x = 1; x < m_average_yaw_vector.size(); x++){
    l_yaw_vector.push_back(m_average_yaw_vector.at(x));
  }
  l_yaw_vector.push_back(l_yaw);
  m_average_yaw_vector = l_yaw_vector;
  return l_yaw;
}

int Inertial::get_average_pitch(){
  return 0;
}

int Inertial::get_average_roll(){
  return 0;
}

int Inertial::get_average_yaw(){
  return 0;
}

int Inertial::get_pitch_rate(){
  return 0;
}

int Inertial::get_roll_rate(){
  return 0;
}

int Inertial::get_yaw_rate(){
  return 0;
}

int Inertial::get_pitch_acceleration(){
  return 0;
}

int Inertial::get_roll_acceleration(){
  return 0;
}

int Inertial::get_yaw_acceleration(){
  return 0;
}

bool Inertial::is_calibrating(){
  return 0;
}

/* Setter Function */
void Inertial::set_port(short const p_port){
  m_port = p_port;
  m_settings.store_int("Port", m_port);
}
