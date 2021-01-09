#include "robot/robot_main.hpp"

#ifndef BUTTON_CLASS_H
#define BUTTON_CLASS_H

namespace GUI{
  class Button{
  private:
    std::string m_name{};

    lv_obj_t* m_button{};
    lv_obj_t* m_label{};

    short m_xOrigin{};
    short m_yOrigin{};
    short m_width{};
    short m_height{};

    std::string m_text{};

    bool m_current_state{false};
    bool m_previous_state{false};

    lv_style_t* m_style_pressed{};
    lv_style_t* m_style_released{};

    /*Required Variles for Change Screen Action*/
    bool m_change_screen = false;
    std::string m_change_screen_ID;

    /*Required Variles for Change Varible Value Action*/
    bool m_connected_double = false;
    double* m_connected_double_pointer;
    double m_connected_double_value;

    /*Required Variles for Increment Varible Screen Action*/
    bool m_connected_increment = false;
    double* m_connected_increment_pointer;
    double m_connected_increment_value;

    /*Required Varibles for Run Function*/
    bool m_preform_function = false;
    std::function<int()> m_run_function;

  public:
    /* Constructors */
    Button(std::string const p_name, std::string const p_text, short const p_yOrigin, short const p_xOrigin, short const p_width, short const p_height, lv_style_t& p_style_pressed, lv_style_t& p_style_released);

    /* Getter Function */
    std::string get_name(){ return m_name; }

    short get_xOrigin(){ return m_xOrigin; }

    short get_YOrigin(){ return m_yOrigin; }

    short get_width(){ return m_width; }

    short get_height(){ return m_height; }

    std::string get_text(){ return m_text; }

    bool get_state();

    lv_style_t* get_style_pressed(){ return m_style_pressed; }

    lv_style_t* get_style_released(){ return m_style_released; }

    //setter function
    void set_text(std::string const p_text){ m_text = p_text; }

    void set_xOrigin(short const p_xOrigin){ m_xOrigin = p_xOrigin; }

    void set_yOrigin(short const p_yOrigin){ m_yOrigin = p_yOrigin; }

    void set_height(short const p_height){ m_height = p_height; }

    void set_width(short const p_width){ m_width = p_width; }

    void set_style_pressed(lv_style_t& p_style_pressed);

    void set_style_released(lv_style_t& p_style_released);

    // Action Functions
    void draw_button(Screen& p_screen);

    void update_button(Screen& p_screen);

    void add_connected_screen(std::string const p_change_screen_ID);

    void add_connected_double(double const p_connected_double_value, double& p_connected_double_pointer);

    void add_connected_increment(double const p_connected_increment_value, double& p_connected_increment_pointer);

    void add_connected_function(std::function<int()> p_run_function);
  };
}

#endif //BUTTON_CLASS_H
