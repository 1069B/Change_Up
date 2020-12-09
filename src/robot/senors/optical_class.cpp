#include "robot/sensors/optical_class.hpp"
#include "robot/robot_class.hpp"

using namespace SENSOR;

Optical::Optical(Robot &p_robot, std::string const p_name, short const p_port, short const p_pwm_value):
  m_robot(p_robot),
  m_settings("Settings.xml", "Sensors", p_name){
    if(m_robot.get_recall_settings()){
      m_name = p_name;
      m_port = m_settings.initialize_int("Port", p_port);
      m_pwm_value = m_settings.initialize_int("Pwm Value", p_pwm_value);
    }
    else{
      m_name = p_name;
      m_port = p_port;
      m_pwm_value  = p_pwm_value;
    }
}

//Setter Functions
void Optical::set_led_pwm(short const p_pwm_value){
  m_pwm_value = p_pwm_value;
  m_settings.store_int("Pwm Value", p_pwm_value);
}

void Optical::set_port(short const p_port){
  m_port = p_port;
  m_settings.store_int("Port", p_port);
}
