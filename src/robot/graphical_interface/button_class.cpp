#include "robot/graphical_interface/button_class.hpp"
#include "robot/graphical_interface/screen_class.hpp"
#include "robot/devices/timer_class.hpp"

using namespace GUI;

/* Constructor */
Button::Button(std::string const p_name, std::string const p_text, short const p_yOrigin, short const p_xOrigin, short const p_width, short const p_height, lv_style_t& p_style_pressed, lv_style_t& p_style_released){
  m_name = p_name;
  m_text = p_text;
  m_xOrigin = p_xOrigin;
  m_yOrigin = p_yOrigin;
  m_height = p_height;
  m_width = p_width;
  m_style_pressed = &p_style_pressed;
  m_style_released = &p_style_released;
}

/* Getter Fucntions */
bool Button::get_state(){
  return lv_btn_get_state(m_button);
}

/* Setter Fucntions */
void Button::set_style_pressed(lv_style_t& p_style_pressed){
  m_style_pressed = &p_style_pressed;
  lv_btn_set_style(m_button, LV_BTN_STYLE_PR, m_style_released);
}

void Button::set_style_released(lv_style_t& p_style_released){
  m_style_released = &p_style_released;
  lv_btn_set_style(m_button, LV_BTN_STYLE_REL, m_style_pressed);
}

/* Action Fucntions */
void Button::draw_button(Screen& p_screen){
  m_button = lv_btn_create(p_screen.get_screen(), NULL);
  m_label = lv_label_create(m_button, NULL);

  lv_obj_align(m_button, p_screen.get_screen(), LV_ALIGN_IN_TOP_LEFT, m_xOrigin, m_yOrigin);
  lv_obj_set_size(m_button, m_width, m_height);
  lv_btn_set_style(m_button, LV_BTN_STYLE_REL, m_style_pressed);
  lv_btn_set_style(m_button, LV_BTN_STYLE_PR, m_style_released);
  lv_label_set_text(m_label, m_text.c_str());
  update_button(p_screen);
}

void Button::update_button(Screen& p_screen){
  if(p_screen.m_displayed){
    m_current_state = lv_btn_get_state(m_button);
  }
  if(m_current_state == false && m_previous_state == true){
    if(m_change_screen){
      Screen::s_next_screen_name = m_change_screen_ID;
      Screen::s_timer.set_flag_delay(100);
    }

    if(m_connected_double)
      *m_connected_double_pointer = m_connected_double_value;

    if(m_connected_increment)
      *m_connected_increment_pointer += m_connected_increment_value;

    if(m_preform_function)
      m_run_function();
  }
  m_previous_state = m_current_state;
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
