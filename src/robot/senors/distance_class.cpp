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
  return pros::c::distance_get(m_port);
}

int Distance::get_average_distance(){
  int distance = get_distance();

  std::vector<int> distance_average_vector;
  for(int x = 1; x < m_average_distance_vector.size(); x++){
    distance_average_vector.push_back(m_average_distance_vector.at(x));
  }
  distance_average_vector.push_back(distance);
  m_average_distance_vector = distance_average_vector;

  int sum = 0;
  for(int x : m_average_distance_vector){
    sum += x;
  }

  
  if(sum == 0){
    return 0;
  }
  return sum/m_average_distance_vector.size();
}

/* Setter Function */
void Distance::set_port(short const p_port){
  m_port = p_port;
  m_settings.store_int("Port", m_port);
}
