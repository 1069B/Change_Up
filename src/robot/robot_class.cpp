#include "robot/robot_class.hpp"
#include "robot/devices/motor_class.hpp"

Robot::Robot(){
  m_recall_settings = m_settings.intitialize_bool("Recall_Settings", false);
}



Motor& Robot::add_motor(std::string const p_name, short const p_port, pros::motor_gearset_e_t const p_motor_gearset, bool const p_reversed){
  for(int x = 0; x < m_motor_list.size(); x++){
    if(m_motor_list.at(x)->get_name() == p_name)
      return *m_motor_list.at(x);
  }

  Motor* l_new_motor{new Motor(*this, p_name, p_port, p_motor_gearset, p_reversed)};
  m_motor_list.push_back(l_new_motor);
  return *l_new_motor;
}
