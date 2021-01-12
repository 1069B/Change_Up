#include "robot/robot_main.hpp"

#ifndef LIST_CLASS_H
#define LIST_CLASS_H

namespace GUI{
  class List{
  private:
    short m_xOrigin{};
    short m_yOrigin{};
    short m_length{};
    short m_width{};

    lv_obj_t* m_list{};

    lv_style_t* m_background_style{};
    lv_style_t* m_selected_style{};
    lv_style_t* m_scrollbar_style{};

    unsigned short m_state{};

    std::vector<std::string>& m_list_options;

    /* Connected Int */
    bool m_conected_int{false};
    int* m_connected_int_pointer{};
    std::vector<int>* m_connected_int_values{};

  public:
    /*  Constuctors  */
    List(short const p_xOrgin, short const p_yOrgin, short const p_length, short const p_width, std::vector<std::string>& p_list_options,
      unsigned short p_state, lv_style_t* p_background_style ,lv_style_t* p_selected_style, lv_style_t* p_scrollbar_style);

    /*  Getting Function  */
    short get_xOrgin(){ return m_xOrigin; }

    short get_yOrigin(){ return m_yOrigin; }

    short get_length(){ return m_length; }

    short get_width(){ return m_width; }

    lv_style_t* get_background_style(){ return m_background_style; }

    lv_style_t* get_selected_style(){ return m_selected_style; }

    lv_style_t* get_scrollbar_style(){ return m_scrollbar_style; }

    unsigned short get_state(){ return m_state; }

    std::vector<std::string>& get_list_options(){ return m_list_options; }

    /*  Setter Function  */
    void set_xOrgin(short const p_xOrgin){ m_xOrigin = p_xOrgin; }

    void set_yOrgin(short const p_yOrgin){ m_yOrigin = p_yOrgin; }

    void set_legnth(short const p_length){ m_length = p_length; }

    void set_width(short const p_width){ m_width = p_width; }

    void set_background_style(lv_style_t& p_background_style){ m_background_style = &p_background_style; }

    void set_selected_style(lv_style_t& p_selected_style){ m_selected_style = &p_selected_style; }

    void set_scrollbar_style(lv_style_t& p_scrollbar_style){ m_scrollbar_style = &p_scrollbar_style; }

    void set_state(unsigned short const p_state);

    /*  Action Function */
    void draw_list(Screen& p_screen);

    void update_list();

    void add_connected_int(int& p_connected_int_pointer, std::vector<int>& p_connected_int_values);
  };
}

#endif // LIST_CLASS_H
