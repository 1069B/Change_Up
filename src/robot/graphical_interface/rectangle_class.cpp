#include "robot/graphical_interface/rectangle_class.hpp"

/*  Constuctors  */
Rectangle::Rectangle(){

}

/*  Setter Function  */
void Rectangle::set_xOrgin(const short p_xOrgin){
 m_xOrigin = p_xOrgin;
}

void Rectangle::set_yOrgin(const short p_yOrgin){
  m_yOrigin = p_yOrgin;
}

void Rectangle::set_legnth(const short p_length){
  m_length = p_length;
}

void Rectangle::set_width(const short p_width){
  m_width = p_width;
}

void Rectangle::set_style(lv_style_t& p_style){
  m_style = &p_style;
}
