#include "robot/graphical_interface/rectangle_class.hpp"

/*  Constuctors  */
Rectangle::Rectangle(short const p_xOrgin, short const p_yOrgin, short const p_length, short const p_width, lv_style_t& p_style){
  m_xOrigin = p_xOrgin;
  m_yOrigin = p_yOrgin;
  m_length = p_length;
  m_width = p_width;
  m_style = &p_style;
}

/*  Action Function */
void Rectangle::draw_rectangle(){
  m_rectangle = lv_obj_create(lv_scr_act(), NULL); // TODO: Change parent
  lv_obj_set_size(m_rectangle, m_length, m_width);
  lv_obj_set_style(m_rectangle, m_style);
  lv_obj_align(m_rectangle, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, m_xOrigin, m_yOrigin); // TODO: Change parent
}

void Rectangle::update_rectangle(){
  lv_obj_set_style(m_rectangle, m_style);
}
