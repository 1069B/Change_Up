#include "main.h"

#ifndef CONTROLLER_CLASS_H
#define CONTROLLER_CLASS_H

namespace CONTROLLER{
  class Button{
  private:
    pros::controller_id_e_t m_controller_type{};// Master or Partner
    pros::controller_digital_e_t m_button_type{};// Which Button

    bool m_state{};
    bool m_previous_state{};

    std::function<void()> m_callback_pressed{};
    std::function<void()> m_callback_released{};
  public:
    /*  Constuctors  */
    Button( pros::controller_id_e_t const p_controller_type, pros::controller_digital_e_t const p_button_type);

    /*  Getting Function  */
    bool get_state(){ return m_state; }

    bool get_previous_state(){ return m_previous_state; }

    std::function<void()> get_callback_pressed(){ return m_callback_pressed; }

    std::function<void()> get_callback_released(){ return m_callback_released; }

    /*  Setter Function  */
    void set_previous_state(bool const p_previous_state){ m_previous_state = p_previous_state; }

    void set_callback_pressed(std::function<void()> p_callback_pressed){ m_callback_pressed = p_callback_pressed; }

    void set_callback_released(std::function<void()> p_callback_released){ m_callback_released = p_callback_released; }

    /*  Action Functions */
    void check_state();

    bool check_callback();
  };

  class Joystick{
  private:
    pros::controller_id_e_t m_controller_type;
    pros::controller_analog_e_t m_axis_type;

    short m_percent{};
  public:
    /*  Constuctors  */
    Joystick(pros::controller_id_e_t p_controller_type, pros::controller_analog_e_t p_axis_type);
    /*  Getting Function  */
    short get_percent(){ return m_percent; }

    /*  Setter Function  */
    void set_percent(short p_percent){ m_percent = p_percent; }

    /*  Action Function */
    void check_percent();
  };

  class Controller{
  private:
    pros::controller_id_e_t m_controller_type{};
  public:
    Button ButtonL1;
    Button ButtonL2;
    Button ButtonR1;
    Button ButtonR2;
    Button ButtonUp;
    Button ButtonDown;
    Button ButtonLeft;
    Button ButtonRight;
    Button ButtonX;
    Button ButtonB;
    Button ButtonY;
    Button ButtonA;
    Joystick Axis1;
    Joystick Axis2;
    Joystick Axis3;
    Joystick Axis4;

    /*  Constuctors  */
    Controller(const pros::controller_id_e_t p_controller_type);

    /*  Getting Function  */
    int get_connected(){ return pros::c::controller_is_connected(m_controller_type); };

    int get_battery_level(){ return pros::c::controller_get_battery_level(m_controller_type); };

    /*  Action Functions */
    void clear_screen();

    void print(int const p_row, int const p_col, char* const p_fmt...);

    void rumble(char* const p_rumble_pattern);
  };
}

#endif // CONTROLLER_CLASS_H
