#include "robot/sensors/rotation_class.hpp" // <- Sensors are in the sensor dolder not the devices folder
#include "robot/robot_class.hpp"

using namespace SENSORS;

Rotation::Rotation(Robot& p_robot, std::string const p_name, short const p_port, bool const p_reversed, int const p_position):
m_robot(p_robot),
m_settings("Settings.xml", "Sensors", p_name){
  if(m_robot.get_recall_settings()){
    m_name = p_name;
    m_port = m_settings.initialize_int("Port", p_port);
    m_reversed = m_settings.initialize_bool("Reversed", p_reversed);
    m_position = m_settings.initialize_int("Position", p_position);
  }
  else{
    m_name = p_name;
    m_port = p_port;
    m_reversed = p_reversed;
    m_position = p_position;
  }

}
// Setter Functions
void Rotation::set_position(short const p_port, int p_position){
  m_port = p_port;
  m_settings.store_int("Port", m_port);
}
