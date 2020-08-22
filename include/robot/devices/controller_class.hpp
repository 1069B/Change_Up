#include "main.h"

#ifndef CONTROLLER_CLASS_H
#define CONTROLLER_CLASS_H

namespace CONTROLLER{
  class Button{
  private:
    pros::controller_id_e_t m_controller_type;// Master or Partner
    pros::controller_digital_e_t m_button_type;// Which Button

    bool m_state{};

    std::function<void()> m_callback_function{};
    int m_callback_delay_time{};
  public:
    /*  Constuctors  */
    Button();

    /*  Getting Function  */
    bool get_state(){ return m_state; }

    std::function<void()> get_callback_function(){ return m_callback_function; }

    int get_callback_delay_time(){ return m_callback_delay_time; }

    /*  Setter Function  */
    void set_callback_delay_time(int p_callback_delay_time){ m_callback_delay_time = p_callback_delay_time; }

    void set_callback_function(std::function<void()> p_callback_function){ m_callback_function = p_callback_function; }

    /*  Action Functions */
    bool check_callback();
  };

  class Joystick{
  private:
    pros::controller_id_e_t m_controller_type;
    pros::controller_analog_e_t m_axis_type;

    short m_percent{};
  public:
    /*  Constuctors  */
    Joystick();
    /*  Getting Function  */
    short get_percent(){ return m_percent; }

    /*  Setter Function  */
    void set_percent(short p_percent){ m_percent = p_percent; }
  };

}

class Controller{
private:

public:
  /*  Constuctors  */
  Controller();
  /*  Getting Function  */

  /*  Setter Function  */

  /*  Action Functions */
  CONTROLLER::Button ButtonL1;
  CONTROLLER::Button ButtonL2;
  CONTROLLER::Button ButtonR1;
  CONTROLLER::Button ButtonR2;
  CONTROLLER::Button ButtonUp;
  CONTROLLER::Button ButtonDown;
  CONTROLLER::Button ButtonLeft;
  CONTROLLER::Button ButtonRight;
  CONTROLLER::Button ButtonX;
  CONTROLLER::Button ButtonB;
  CONTROLLER::Button ButtonY;
  CONTROLLER::Button ButtonA;
  CONTROLLER::Joystick Axis1;
  CONTROLLER::Joystick Axis2;
  CONTROLLER::Joystick Axis3;
  CONTROLLER::Joystick Axis4;
};



#endif // CONTROLLER_CLASS_H
