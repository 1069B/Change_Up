#include "robot/devices/motor_class.hpp"
#include "robot/robot_class.hpp"

Motor::Motor(Robot &p_robot, std::string const p_name, short const p_port, pros::motor_gearset_e_t const p_motor_gearset, bool const p_reversed):
m_robot(p_robot){
  if(m_robot.get_recall_settings()){
    m_port = m_settings.intitialize_int("Port", p_port);
    m_motor_gearset = (pros::motor_gearset_e_t)m_settings.intitialize_int("Gearset", (int)p_motor_gearset);
    m_reversed = m_settings.intitialize_bool("Reversed", p_reversed);
  }
  else{
    m_name = p_name;
    m_port = p_port;
    m_motor_gearset = p_motor_gearset;
    m_reversed = p_reversed;
  }
}
