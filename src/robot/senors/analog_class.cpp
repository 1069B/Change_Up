#include "robot/robot_class.hpp"
#include "robot/devices/data_storage_class.hpp"
#include "robot/sensors/analog_class.hpp"

using namespace SENSOR;

Analog_Pair::Analog_Pair(Robot &p_robot, std::string const p_name, short const p_expander_port, short const p_first_port, short const p_second_port, double p_lower_bound, double p_upper_bound):
m_robot(p_robot),
m_settings(*new Data_Storing("Settings.xml", "Digital", p_name)){
  if(m_robot.get_recall_settings()){
    m_name = p_name;
    m_first_port = m_settings.initialize_int("Port", m_first_port);

    m_name = p_name;
    m_expander_port = p_expander_port;
    m_first_port = p_first_port;
    m_second_port = p_second_port;
    m_lower_bound = p_lower_bound;
    m_upper_bound = p_upper_bound;
  }
  else{
    m_name = p_name;
    m_expander_port = p_expander_port;
    m_first_port = p_first_port;
    m_second_port = p_second_port;
    m_lower_bound = p_lower_bound;
    m_upper_bound = p_upper_bound;
  }

  if(m_expander_port != 0){
    pros::c::ext_adi_port_set_config(m_expander_port, m_first_port, pros::E_ADI_ANALOG_IN);
    pros::c::ext_adi_port_set_config(m_expander_port, m_second_port, pros::E_ADI_ANALOG_IN);
  }
}


double Analog_Pair::get_first_value(){
  if(m_expander_port == 0)
    return pros::c::adi_analog_read(m_first_port);
  return pros::c::ext_adi_analog_read_calibrated(m_expander_port, m_first_port);
  return 1;
}

double Analog_Pair::get_second_value(){
  if(m_expander_port == 0)
    return pros::c::adi_analog_read(m_second_port);
  return pros::c::ext_adi_analog_read_calibrated(m_expander_port, m_second_port);
  return 1;
}

bool Analog_Pair::is_both(){
  if(inside_range(get_first_value(), m_lower_bound, m_upper_bound) && inside_range(get_second_value(), m_lower_bound, m_upper_bound))
    return true;
  return false;
}

bool Analog_Pair::is_either(){
  if(inside_range(get_first_value(), m_lower_bound, m_upper_bound) || inside_range(get_second_value(), m_lower_bound, m_upper_bound))
    return true;
  return false;
}