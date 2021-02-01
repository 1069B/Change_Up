#include "robot/robot_main.hpp"

#ifndef RECTANGLE_CLASS_H
#define RECTANGLE_CLASS_H

namespace GUI{
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
    Rectangle(short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, lv_style_t& p_style);

    /*  Getting Function  */

    short get_xOrgin(){ return m_xOrigin; }

    short get_yOrigin(){ return m_yOrigin; }

    short get_length(){ return m_length; }

    short get_width(){ return m_width; }

    lv_style_t* get_style(){ return m_style; }

    /*  Setter Function  */
    void set_xOrigin(short const p_xOrgin){ m_xOrigin = p_xOrgin; }

    void set_yOrigin(short const p_yOrigin){ m_yOrigin = p_yOrigin; }

    void set_legnth(short const p_length){ m_length = p_length; }

    void set_width(short const p_width){ m_width = p_width; }

    void set_style(lv_style_t& p_style){ m_style = &p_style; }

    /*  Action Function */
    void draw_rectangle(Screen& p_screen);

    void update_rectangle();
  };
}

#endif // RECTANGLE_CLASS_H
