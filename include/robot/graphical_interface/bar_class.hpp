#include "robot/robot_main.hpp"

#ifndef BAR_CLASS_H
#define BAR_CLASS_H

namespace GUI{
  class Bar{
  private:
    short m_xOrigin{};
    short m_yOrigin{};
    short m_length{};
    short m_width{};

    int m_position{};
    int m_range_minimum{};
    int m_range_maximum{};

    lv_obj_t* m_bar{};
    lv_style_t* m_bar_style{};
    lv_style_t* m_indicator_style{};

    /*Required Variles for a Connected Int*/
    bool m_connected_int = false;
    int* m_connected_int_pointer;

  public:
    /* Constuctors */
    Bar(short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, int const p_position, int const p_range_minimum, int const p_range_maximum, lv_style_t&  p_bar_style, lv_style_t&  p_indicator_style);

    /* Getter Functions */
    short get_xOrigin(){ return m_xOrigin; }

    short get_yOrigin(){ return m_yOrigin; }

    short get_length(){ return m_length; }

    short get_width(){ return m_width; }

    int get_position(){ return m_position; }

    int get_range_minimum(){ return m_range_minimum; }

    int get_range_maximum(){ return m_range_maximum; }

    lv_style_t* get_bar_style(){ return m_bar_style; }

    lv_style_t* get_indicator_style(){ return m_indicator_style; }

    /* Setter Functions */
    void set_xOrigin(short const p_xOrigin){ m_xOrigin = p_xOrigin; }

    void set_yOrigin(short const p_yOrigin){ m_yOrigin = p_yOrigin; }

    void set_length(short const p_length){ m_length = p_length; }

    void set_width(short const p_width){ m_width = p_width; }

    void set_position(int const p_position);

    void set_range(short const p_range_maximum, short const p_range_minimum);

    void set_bar_style(lv_style_t& p_bar_style);

    void set_indicator_style(lv_style_t& p_indicator_style);

    /* Action Functions */
    void draw_bar(Screen& p_screen);

    void update_bar();

    void add_connected_int(int& p_connected_int_pointer);
  };
}

#endif //BAR_CLASS_H
