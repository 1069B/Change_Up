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
    std::vector<Roller*> m_roller_vector;
    std::vector<Bar*> m_bar_vector;
    std::vector<Button*> m_button_vector;
    std::vector<Switch*> m_switch_vector;

    std::string m_screen_name;

    bool m_displayed{false};

    /* Screen Relationship */
    std::function<bool()> m_related_function;
    std::string m_error_screen_name;
    bool m_related_screen_inversed {false};
    bool m_screen_relation {false};

    /* Static Members */
    static std::vector<Screen*> s_screen_vector;

    static std::string s_current_screen_name;
    static std::string s_previous_screen_name;
    static std::string s_next_screen_name;

    static Screen& s_home_screen;
    static Screen& s_disconnected_screen;

    static Screen* s_current_screen_pointer;

    static Data_Storing s_settings;
    static Timer s_timer;

    friend class Button;

  public:
    /* Constructor */
    Screen(const std::string p_name);
    Screen(const std::string p_name, std::function<bool()> p_function, std::string const p_screen_name, bool const p_inversed = false);

    /* Getter Functions */
    std::string get_screen_name(){return m_screen_name; }

    lv_obj_t* get_screen(){return m_screen; }

    bool get_displayed(){ return m_displayed; }

    static Screen& find_screen(std::string const p_screen_name);

    /* Add Functions */
    Rectangle& create_rectanlge(short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, lv_style_t& p_style);

    Label& create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, lv_label_align_t const p_alignment = LV_ALIGN_IN_TOP_LEFT);
    Label& create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, int& p_int_value, lv_label_align_t const p_alignment = LV_ALIGN_IN_TOP_LEFT);
    Label& create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, double& p_double_value, lv_label_align_t const p_alignment = LV_ALIGN_IN_TOP_LEFT);
    Label& create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::string& p_string_value, lv_label_align_t const p_alignment = LV_ALIGN_IN_TOP_LEFT);
    Label& create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, bool& p_bool_value, lv_label_align_t const p_alignment = LV_ALIGN_IN_TOP_LEFT);

    Label& create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<int()> p_int_value, lv_label_align_t const p_alignment = LV_ALIGN_IN_TOP_LEFT);
    Label& create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<double()> p_double_value, lv_label_align_t const p_alignment = LV_ALIGN_IN_TOP_LEFT);
    Label& create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<std::string()> p_string_value, lv_label_align_t const p_alignment = LV_ALIGN_IN_TOP_LEFT);
    Label& create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<bool()> p_bool_value, lv_label_align_t const p_alignment = LV_ALIGN_IN_TOP_LEFT);

    Roller& create_roller(short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, std::vector<std::string>& p_roller_options, unsigned short p_state, lv_style_t& p_background_style, lv_style_t& p_selected_style);

    Bar& create_bar(short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, int const p_position, int const p_range_minimum, int const p_range_maximum, lv_style_t&  p_bar_style, lv_style_t&  p_indicator_style);

    Button& create_button(std::string const p_text, short const p_yOrigin, short const p_xOrigin, short const p_width, short const p_height, lv_style_t& p_style_pressed = GUI_STYLES::default_button_pressed, lv_style_t& p_style_released  = GUI_STYLES::default_button_released);

    Switch& create_switch(short const p_xOrgin, short const p_yOrgin, int const p_state, lv_style_t& p_background_style,
      lv_style_t& p_indicator_style, lv_style_t& p_true_style, lv_style_t& p_false_style);

    static Screen& create_screen(const std::string p_name);
    static Screen& create_screen(const std::string p_name, std::function<bool()> p_function, std::string const p_screen_name, bool const m_inversed = false);

    /* Action */
    void draw_screen();

    void update_screen();

    void delete_screen();

    void add_relationship(std::function<bool()> p_function, std::string const p_screen_name, bool const p_inversed = false);

    static void initialize(Robot& p_robot);

    static void draw_current_screen();

    static void task();
  };
}

#endif // SCREEN_CLASS_H
