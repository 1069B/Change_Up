#include "main.h"

#ifndef BAR_CLASS_H
#define BAR_CLASS_H

//namespace GUI
class Bar{
private:
  short m_xOrigin{};
  short m_yOrigin{};

  lv_obj_t* m_bar1{}; //default
  lv_obj_t* m_bar2{};
  lv_obj_t* m_bar1_label{}; //default
  lv_obj_t* m_bar2_label{};
  lv_style_t* m_bar_style{};
  lv_style_t* m_indicator_style{};

public:
  /* Constuctors */
  Bar(lv_obj_t* m_bar1, lv_obj_t* m_bar2, v_obj_t* m_bar1_label, lv_obj_t* m_bar2_label, lv_style_t* m_bar_style, lv_style_t* m_indicator_style);
  /* Getter Functions */
  short get_xOrigin(){ return m_xOrigin; }
  short get_yOrigin(){ return m_yOrigin; }
  lv_obj_t* get_bar1(){ return m_bar1; }
  lv_obj_t* get_bar2(){ return m_bar2; }
  lv_obj_t* get_bar1_label(){ return m_bar1_label; }
  lv_obj_t* get_bar2_label(){ return m_bar2_label;}
  lv_style_t* get_m_bar_style(){ return m_bar_style; }
  lv_style_t*
  /* Setter Functions */
}

#endif //BAR_CLASS_H
