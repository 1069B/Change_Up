#include "robot/graphical_interface/switch_class.hpp"

/*  Constuctors  */
Switch::Switch(short const p_xOrgin, short const p_yOrgin, int const p_state, lv_style_t& p_background_style,
  lv_style_t& p_indicator_style, lv_style_t& p_true_style, lv_style_t& p_false_style){
  m_xOrigin = p_xOrgin;
  m_yOrigin = p_yOrgin;
  m_state = p_state;

  m_background_style = &p_background_style;
  m_indicator_style = &p_indicator_style;
  m_true_style = &p_true_style;
  m_false_style = &p_false_style;
}

/* Setter Functions*/
void Switch::set_state(bool const p_state){
  m_state = p_state;
  if(m_state)
    lv_sw_on(m_switch);
  else
    lv_sw_off(m_switch);
  update_switch();
}

/*  Action Function */
void Switch::draw_switch(){
  m_switch = lv_sw_create(lv_scr_act(), NULL); // TODO: Change parent
  lv_sw_set_style(m_switch, LV_SW_STYLE_BG, m_background_style);
  lv_sw_set_style(m_switch, LV_SW_STYLE_INDIC, m_indicator_style);
  lv_sw_set_style(m_switch, LV_SW_STYLE_KNOB_ON, m_true_style);
  lv_sw_set_style(m_switch, LV_SW_STYLE_KNOB_OFF, m_false_style);
  lv_obj_align(m_switch, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, m_xOrigin, m_yOrigin); // TODO: Change parent

  if(m_state)
    lv_sw_on(m_switch);
  else
    lv_sw_off(m_switch);

  update_switch();
}

void Switch::update_switch(){
  m_state = lv_sw_get_state(m_switch);

  if(m_state){
    if(m_connected_bool)
      *m_connected_bool_pointer = true;
    if(m_connected_int_pointer)
      *m_connected_int_pointer = m_connected_int_value_true;
  }

  else{
    if(m_connected_bool)
      *m_connected_bool_pointer = false;
    if(m_connected_int_pointer)
      *m_connected_int_pointer = m_connected_int_value_false;
  }
}

void Switch::add_connected_bool(bool& p_connected_bool_pointer){
  m_connected_bool_pointer = &p_connected_bool_pointer;
  m_connected_bool = true;
}

void Switch::add_connected_int(int& p_connected_int_pointer, int const p_true_value, int const p_false_value){
  m_connected_int_pointer = &p_connected_int_pointer;
  m_connected_int_value_true = p_true_value;
  m_connected_int_value_false = p_false_value;
  m_connected_int = true;
}
