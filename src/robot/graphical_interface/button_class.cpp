#include "robot/graphical_interface/button_class.hpp"

using namespace GUI;

//Constructors
Button::Button(std::string const p_text, bool const p_state,short const p_yOrigin, short const p_xOrigin, short const p_width, short const p_height, lv_style_t& p_style_pressed, lv_style_t& p_style_released){
  m_xOrigin = p_xOrigin;
  m_yOrigin = p_yOrigin;
  m_height = p_height;
  m_width = p_width;
  m_state = p_state;
  m_style_pressed = &p_style_pressed;
  m_style_released = &p_style_released;
}

void Button::set_state(bool const p_state){
  m_state = p_state;
}

void Button::set_style_pressed(lv_style_t& p_style_pressed){
  m_style_pressed = &p_style_pressed;
}

void Button::set_style_released(lv_style_t& p_style_released){
  m_style_released = &p_style_released;
}
void Button::draw_button(){

}

void Button::update_button(){

}

void Button::add_connected_screen(std::string const p_change_screen_ID){
  m_change_screen_ID = p_change_screen_ID;
  m_change_screen = true;
}

void Button::add_connected_double(double const p_connected_double_value, double& p_connected_double_pointer){
  m_connected_double_value = p_connected_double_value;
  m_connected_double_pointer = &p_connected_double_pointer;
  m_connected_double = true;
}

void Button::add_connected_increment(double const p_connected_increment_value, double& p_connected_increment_pointer){
  m_connected_increment_value = p_connected_increment_value;
  m_connected_increment_pointer = &p_connected_increment_pointer;
  m_connected_increment = true;
}

void Button::add_connected_function(std::function<int()> p_run_function){
  m_run_function = p_run_function;
  m_preform_function = true;
}
