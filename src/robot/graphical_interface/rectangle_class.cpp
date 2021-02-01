#include "robot/graphical_interface/rectangle_class.hpp"
#include "robot/graphical_interface/screen_class.hpp"

/*  Constuctors  */
GUI::Rectangle::Rectangle(short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, lv_style_t& p_style){
  m_xOrigin = p_xOrigin;
  m_yOrigin = p_yOrigin;
  m_length = p_length;
  m_width = p_width;
  m_style = &p_style;
}

/*  Action Function */
void GUI::Rectangle::draw_rectangle(Screen& p_screen){
  m_rectangle = lv_obj_create(p_screen.get_screen(), NULL); // TODO: Change parent
  lv_obj_set_size(m_rectangle, m_length, m_width);
  lv_obj_set_style(m_rectangle, m_style);
  lv_obj_align(m_rectangle, p_screen.get_screen(), LV_ALIGN_IN_TOP_LEFT, m_xOrigin, m_yOrigin); // TODO: Change parent
}

void GUI::Rectangle::update_rectangle(){
  lv_obj_set_style(m_rectangle, m_style);
}
