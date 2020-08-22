#include "robot/devices/controller_class.hpp"

using namespace CONTROLLER;

Button::Button(){

}

bool Button::check_callback(){
  if(get_state()){ //TODO: ADD Callback delay once Timer is done.
    m_callback_function();
    return true;
  }
  return false;
}
