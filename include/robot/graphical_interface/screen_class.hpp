#include "robot/robot_main.hpp"

#ifndef SCREEN_CLASS_H
#define SCREEN_CLASS_H

namespace GUI{
  class Screen{
  private:
    lv_obj_t* m_screen;
    lv_style_t* m_style;

    std::vector<Rectangle*> m_rectangle_vector;
    std::vector<Label*> m_label_vector;
    std::vector<List*> m_list_vector;
    std::vector<Bar*> m_bar_vector;
    std::vector<Button*> m_button_vector;
    std::vector<Switch*> m_switch_vector;

    std::string m_screen_name;
    std::string m_error_screen;

    bool m_displayed{false};

    /* Static Members */
    static std::vector<Screen*> s_screen_vector;

    static std::string s_current_screen_name;
    static std::string s_previous_screen_name;
    static std::string s_next_screen_name;

    static Screen* s_current_screen_pointer;// TODO:: Created Deafult Screen
    static Screen* s_next_screen_pointer;

    static Data_Storing s_settings;


  public:
    /* Constructor */
    Screen(const std::string p_name);

    /* Getter Functions */
    std::string get_screen_name(){return m_screen_name; }

    lv_obj_t* get_screen(){return m_screen; }

    bool get_displayed(){ return m_displayed; }

    /* Add Functions */
    Rectangle& create_rectanlge(std::string const p_name, short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, lv_style_t& p_style);


    Label& create_label(std::string const p_name, short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text);
    template <typename T = std::string>
    Label& create_label(std::string const p_name, short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, T value);

    List& create_list(std::string const p_name, short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, std::vector<std::string>& p_list_options,
      unsigned short p_state, lv_style_t* p_background_style, lv_style_t* p_selected_style, lv_style_t* p_scrollbar_style);

    Bar& create_bar(std::string const p_name, short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, int const p_position, int const p_range_minimum, int const p_range_maximum, lv_style_t&  p_bar_style, lv_style_t&  p_indicator_style);

    Button& create_button(std::string const p_name, std::string const p_text, short const p_yOrigin, short const p_xOrigin, short const p_width, short const p_height, lv_style_t& p_style_pressed, lv_style_t& p_style_released);

    Switch& create_switch(std::string const p_name, short const p_xOrgin, short const p_yOrgin, int const p_state, lv_style_t& p_background_style,
      lv_style_t& p_indicator_style, lv_style_t& p_true_style, lv_style_t& p_false_style);

    static Screen& create_screen(const std::string p_name);

    /* Action */
    void draw_screen();

    void update_screen();

    void delete_screen();

    static void task();
  };
}

#endif // SCREEN_CLASS_H
