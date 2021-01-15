#include "robot/graphical_interface/bar_class.hpp"
#include "robot/graphical_interface/screen_class.hpp"

using namespace GUI;

/* Constructors */
Bar::Bar(short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, int const p_position, int const p_range_minimum, int const p_range_maximum, lv_style_t&  p_bar_style, lv_style_t&  p_indicator_style){
  m_xOrigin = p_xOrigin;
  m_yOrigin = p_yOrigin;
  m_length = p_length;
  m_width = p_width;
  m_position = p_position;
  m_range_minimum = p_range_minimum;
  m_range_maximum = p_range_maximum;
  m_bar_style = &p_bar_style;
  m_indicator_style = &p_indicator_style;
}

/* Setter Functions */
void Bar::set_range(short const p_range_maximum, short const p_range_minimum){
  m_range_maximum = p_range_maximum;
  m_range_minimum = p_range_minimum;
  lv_bar_set_range(m_bar, m_range_minimum, m_range_maximum);
}

void Bar::set_position(int const p_position){
  m_position = p_position;
  update_bar();
}

void Bar::set_bar_style(lv_style_t& p_bar_style){
  m_bar_style = &p_bar_style;
  lv_bar_set_style(m_bar, LV_BAR_STYLE_BG, m_bar_style);
}

void Bar::set_indicator_style(lv_style_t& p_indicator_style){
  m_indicator_style = &p_indicator_style;
  lv_bar_set_style(m_bar, LV_BAR_STYLE_INDIC, m_indicator_style);
}

/* Action Functions */
void Bar::draw_bar(Screen& p_screen){
  m_bar = lv_bar_create(p_screen.get_screen(), NULL);// TODO: Add Screen Refernece
  lv_obj_set_size(m_bar, m_length, m_width);
  lv_obj_align(m_bar, NULL, LV_ALIGN_IN_TOP_LEFT, m_xOrigin, m_yOrigin);
  lv_bar_set_value(m_bar, m_position);
  lv_bar_set_range(m_bar, m_range_minimum, m_range_maximum);
  lv_bar_set_style(m_bar, LV_BAR_STYLE_BG, m_bar_style);
  lv_bar_set_style(m_bar, LV_BAR_STYLE_INDIC, m_indicator_style);
}

void Bar::update_bar(){
  lv_bar_set_value(m_bar, m_position);

  if(m_connected_int){
    *m_connected_int_pointer = m_position;
  }
}

void Bar::add_connected_int(int& p_connected_int_pointer){
  m_connected_int_pointer = &p_connected_int_pointer;
  m_connected_int = true;
}
