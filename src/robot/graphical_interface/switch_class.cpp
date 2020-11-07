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
  m_false_style = &p_false_style
}

/*  Action Function */
void Switch::draw_switch(){
  m_switch = lv_sw_create(lv_scr_act(), NULL); // TODO: Change parent
  lv_sw_set_style(m_switch, LV_SW_STYLE_BG, &bg_style);
  lv_sw_set_style(m_switch, LV_SW_STYLE_INDIC, &indic_style);
  lv_sw_set_style(m_switch, LV_SW_STYLE_KNOB_ON, &knob_on_style);
  lv_sw_set_style(m_switch, LV_SW_STYLE_KNOB_OFF, &knob_off_style);
  lv_obj_align(m_switch, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, m_xOrigin, m_yOrigin); // TODO: Change parent

  if(m_state)
    lv_sw_on(m_switch);
  else
    lv_sw_off(m_switch);

}

void Switch::update_switch(){
  if(lv_sw_get_state()){
    m_state = true
  }
  else(){
    m_state = false;
  }
}
