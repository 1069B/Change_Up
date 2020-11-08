#include "main.h"

#ifndef SWITCH_CLASS_H
#define SWITCH_CLASS_H

class Screen;

class Switch{
private:
  short m_xOrigin{};
  short m_yOrigin{};

  lv_obj_t* m_switch{};

  lv_style_t* m_background_style{};
  lv_style_t* m_indicator_style{};
  lv_style_t* m_true_style{};
  lv_style_t* m_false_style{};

  bool m_state{false};

  /*Required Variles for a Connected Bool*/
  bool m_connected_bool = false;
  bool* m_connected_bool_pointer;

  /*Required Variles for a Connected Int*/
  bool m_connected_int = false;
  int* m_connected_int_pointer;
  int m_connected_int_value_true;
  int m_connected_int_value_false;
public:
  /*  Constuctors  */
  Switch(short const p_xOrgin, short const p_yOrgin, int const p_state, lv_style_t& p_background_style,
    lv_style_t& p_indicator_style, lv_style_t& p_true_style, lv_style_t& p_false_style);

  /*  Getter Function  */
  short get_xOrgin(){ return m_xOrigin; }

  short get_yOrigin(){ return m_yOrigin; }

  lv_style_t* get_background_style(){ return m_background_style; }

  lv_style_t* get_indicator_style(){ return m_indicator_style; }

  lv_style_t* get_true_style(){ return m_true_style; }

  lv_style_t* get_false_style(){ return m_false_style; };

  bool get_state(){ return m_state; }

  /*  Setter Function  */
  void set_xOrgin(short const p_xOrgin){ m_xOrigin = p_xOrgin; }

  void set_yOrgin(short const p_yOrgin){ m_yOrigin = p_yOrgin; }

  void set_background_style(lv_style_t& p_background_style){ m_background_style = &p_background_style; }

  void set_indicator_style(lv_style_t& p_indicator_style){ m_indicator_style = &p_indicator_style; }

  void set_switch_true_style(lv_style_t& p_true_style){ m_true_style = &p_true_style; }

  void set_switch_false_style(lv_style_t& p_false_style){ m_false_style = &p_false_style; }

  void set_state(bool const p_state);

  /*  Action Function */
  void draw_switch();// TODO: Add Screen& p_screen

  void update_switch();// TODO: Add Screen& p_screen

  void add_connected_bool(bool& p_connected_bool_pointer);

  void add_connected_int(int& p_connected_int_pointer, int const p_true_value, int const p_false_value);
};

#endif // RECTAGNLE_CLASS_H
