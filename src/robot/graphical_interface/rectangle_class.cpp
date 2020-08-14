#include "robot/graphical_interface/rectangle_class.hpp"

/*  Constuctors  */
Rectangle::Rectangle(){

}

/*  Setter Function  */
void Rectangle::set_xOrgin(short const p_xOrgin){
 m_xOrigin = p_xOrgin;
}

void Rectangle::set_yOrgin(short const p_yOrgin){
  m_yOrigin = p_yOrgin;
}

void Rectangle::set_legnth(short const p_length){
  m_length = p_length;
}

void Rectangle::set_width(short const p_width){
  m_width = p_width;
}

void Rectangle::set_style(lv_style_t& p_style){
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
