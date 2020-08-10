#include "main.h"

#ifndef RECTAGNLE_CLASS_H
#define RECTAGNLE_CLASS_H

class Screen;

class Rectangle{
private:
  short m_xOrigin{};
  short m_yOrigin{};
  short m_length{};
  short m_width{};

  lv_obj_t* m_rectangle{};
  lv_style_t* m_style{};
public:
  /*  Constuctors  */
  Rectangle();

  /*  Getting Function  */
  short get_xOrgin(){ return m_xOrigin; }

  short get_yOrigin(){ return m_yOrigin; }

  short get_length(){ return m_length; }

  short get_width(){ return m_width; }

  lv_style_t* get_style(){ return m_style; }

  /*  Setter Function  */
  void set_xOrgin(short const p_xOrgin);

  void set_yOrgin(short const p_yOrgin);

  void set_legnth(short const p_length);

  void set_width(short const p_width);

  void set_style(lv_style_t& p_style);

  /*  Action Function */
  void draw_rectangle(Screen& p_screen);

  void update_rectangle(Screen& p_screen);
};

#endif // RECTAGNLE_CLASS_H
