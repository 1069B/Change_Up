#include "robot/robot_main.hpp"

#ifndef ROLLER_CLASS_H
#define ROLLER_CLASS_H

namespace GUI{
  class Roller{
  private:
    short m_xOrigin{};
    short m_yOrigin{};
    short m_length{};

    lv_obj_t* m_roller{};

    lv_style_t* m_background_style{};
    lv_style_t* m_selected_style{};

    unsigned short m_state{};

    std::vector<std::string>& m_roller_options;

    /* Connected Int */
    bool m_connected_int{false};
    int* m_connected_int_pointer{};
    std::vector<int>* m_connected_int_values{};

  public:
    /*  Constuctors  */
    Roller(short const p_xOrigin, short const p_yOrigin, short const p_length, std::vector<std::string>& p_list_options,
      unsigned short p_state, lv_style_t& p_background_style ,lv_style_t& p_selected_style);

    /*  Getting Function  */
    short get_xOrigin(){ return m_xOrigin; }

    short get_yOrigin(){ return m_yOrigin; }

    short get_length(){ return m_length; }

    lv_style_t* get_background_style(){ return m_background_style; }

    lv_style_t* get_selected_style(){ return m_selected_style; }

    unsigned short get_state(){ return m_state; }

    std::vector<std::string>& get_roller_options(){ return m_roller_options; }

    /*  Setter Function  */
    void set_xOrigin(short const p_xOrigin){ m_xOrigin = p_xOrigin; }

    void set_yOrigin(short const p_yOrigin){ m_yOrigin = p_yOrigin; }

    void set_legnth(short const p_length){ m_length = p_length; }

    void set_background_style(lv_style_t& p_background_style){ m_background_style = &p_background_style; }

    void set_selected_style(lv_style_t& p_selected_style){ m_selected_style = &p_selected_style; }

    void set_state(unsigned short const p_state);

    /*  Action Function */
    void draw_roller(Screen& p_screen);

    void update_roller();

    void add_connected_int(int& p_connected_int_pointer, std::vector<int>& p_connected_int_values);
  };
}

#endif // ROLLER_CLASS_H
