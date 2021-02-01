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

/* Setter Function */
void Distance::set_port(short const p_port){
  m_port = p_port;
  m_settings.store_int("Port", m_port);
}
