#include "robot/devices/controller_class.hpp"

/* Button Class*/
CONTROLLER::Button::Button(const pros::controller_id_e_t p_controller_type, const pros::controller_digital_e_t p_button_type){
  m_controller_type = p_controller_type;
  m_button_type = p_button_type;
}

void CONTROLLER::Button::check_state(){
  m_state = pros::c::controller_get_digital(m_controller_type, m_button_type);
}

bool CONTROLLER::Button::check_callback(){
  if(get_state() && get_state() != get_previous_state()){
    set_previous_state(get_state());
    m_callback_pressed();
    return 1;
  }
  else if(!get_state() && get_state() != get_previous_state()){
    set_previous_state(get_state());
    m_callback_released();
    return -1;
  }
  return 0;
}

/* Joystick Class */
CONTROLLER::Joystick::Joystick(const pros::controller_id_e_t p_controller_type, const pros::controller_analog_e_t p_axis_type){
  m_controller_type = p_controller_type;
  m_axis_type = p_axis_type;
}

void CONTROLLER::Joystick::check_percent(){
  short l_joystick_raw_value = pros::c::controller_get_analog(m_controller_type, m_axis_type);
  m_percent = (short)((l_joystick_raw_value/127.0)*100.0);

}
