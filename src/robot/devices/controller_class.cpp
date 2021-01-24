#include "robot/devices/controller_class.hpp"

/* Button Class*/
CONTROLLER::Button::Button(const pros::controller_id_e_t p_controller_type, const pros::controller_digital_e_t p_button_type){
  m_controller_type = p_controller_type;
  m_button_type = p_button_type;
}

bool CONTROLLER::Button::get_state(){
  m_state = pros::c::controller_get_digital(m_controller_type, m_button_type);
  return m_state;
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

double CONTROLLER::Joystick::get_percent(){
  double l_joystick_raw_value = pros::c::controller_get_analog(m_controller_type, m_axis_type);
  m_percent = l_joystick_raw_value/127.0;
  return m_percent;
}


/* Controller Class */
 CONTROLLER::Controller::Controller(const pros::controller_id_e_t p_controller_type):
  ButtonL1(p_controller_type, pros::E_CONTROLLER_DIGITAL_L1),
  ButtonL2(p_controller_type, pros::E_CONTROLLER_DIGITAL_L2),
  ButtonR1(p_controller_type, pros::E_CONTROLLER_DIGITAL_R1),
  ButtonR2(p_controller_type, pros::E_CONTROLLER_DIGITAL_R2),
  ButtonUp(p_controller_type, pros::E_CONTROLLER_DIGITAL_UP),
  ButtonDown(p_controller_type, pros::E_CONTROLLER_DIGITAL_DOWN),
  ButtonLeft(p_controller_type, pros::E_CONTROLLER_DIGITAL_LEFT),
  ButtonRight(p_controller_type, pros::E_CONTROLLER_DIGITAL_RIGHT),
  ButtonX(p_controller_type, pros::E_CONTROLLER_DIGITAL_X),
  ButtonB(p_controller_type, pros::E_CONTROLLER_DIGITAL_B),
  ButtonY(p_controller_type, pros::E_CONTROLLER_DIGITAL_Y),
  ButtonA(p_controller_type, pros::E_CONTROLLER_DIGITAL_A),
  Axis1(p_controller_type, pros::E_CONTROLLER_ANALOG_RIGHT_X),
  Axis2(p_controller_type, pros::E_CONTROLLER_ANALOG_RIGHT_Y),
  Axis3(p_controller_type, pros::E_CONTROLLER_ANALOG_LEFT_Y),
  Axis4(p_controller_type, pros::E_CONTROLLER_ANALOG_LEFT_X){
   m_controller_type = p_controller_type;
 }

void CONTROLLER::Controller::clear_screen(){
  pros::c::controller_clear(m_controller_type);
};

void CONTROLLER::Controller::print(int const p_row, int const p_col, char* p_fmt...){// TODO: Remove Variadic Function
  std::string sum = "";
  va_list args;
  va_start(args, p_fmt);
  while(*p_fmt != '\0') {
  	if(*p_fmt == '%'){
  		++p_fmt;
  		if(*p_fmt == 'd'){
  			sum += std::to_string(va_arg(args, int));
        ++p_fmt;
  		}
  		else if(*p_fmt == 'f'){
        sum += std::to_string(va_arg(args, double));
        ++p_fmt;
  		}
  		else if(*p_fmt == 'c'){
        sum += (char)(va_arg(args, int));
        ++p_fmt;
  		}
  		else{
	    	++p_fmt;
	    }
  	}
  	else{
      sum += *p_fmt;
  		++p_fmt;
  	}
  }
  va_end(args);
  int n = sum.length();
  char char_array[n + 1];
  strcpy(char_array, sum.c_str());
  pros::c::controller_set_text(m_controller_type, p_row, p_col, char_array);
  pros::delay(50);
}

void CONTROLLER::Controller::rumble(char* const p_rumble_pattern){
  pros::c::controller_rumble(m_controller_type, p_rumble_pattern);
};
