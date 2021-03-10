#include "robot/robot_class.hpp"
#include "robot/sensors/distance_class.hpp"
#include "robot/devices/data_storage_class.hpp"

using namespace SENSOR;

Distance::Distance(Robot &p_robot, std::string const p_name, short const p_port):
m_robot(p_robot),
m_settings(*new Data_Storing("Settings.xml", "Distance", p_name)){
  if(m_robot.get_recall_settings()){
    m_name = p_name;
    m_port = m_settings.initialize_int("Port", p_port);
  }
  else{
    m_name = p_name;
    m_port = p_port;
  }
}

/* Getter Functions */
int Distance::get_distance(){
  int distance = pros::c::distance_get(m_port); 
  return distance;

  // std::vector<int> distance_average_vector;
  // for(int x = 1; x < m_average_velo_vector.size(); x++){
  //   l_velocity_average_vector.push_back(m_average_velocity_vector.at(x));
  // }
  // l_velocity_average_vector.push_back(l_velocity);
  // m_average_velocity_vector = l_velocity_average_vector;
}

/* Setter Function */
void Distance::set_port(short const p_port){
  m_port = p_port;
  m_settings.store_int("Port", m_port);
}
