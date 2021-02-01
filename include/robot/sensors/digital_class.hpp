#include "robot/robot_main.hpp"

#ifndef DIGITAL_CLASS_H
#define DIGITAL_CLASS_H

namespace SENSOR{
  class Digital{
  private:
    Robot& m_robot;

    /*Settings*/
    std::string m_name{};
    short m_port{};

    Data_Storing& m_settings;
  public:
    /*  Constuctors  */
    Digital(Robot &p_robot, std::string const p_name, short const p_port);

    /*  Getting Functions  */
    std::string get_name(){ return m_name; }

    short get_port(){ return m_port; }

    bool get_new_press(){ return pros::c::adi_digital_get_new_press(m_port); };

    bool get_value(){ return pros::c::adi_digital_read(m_port); };

    /* Setter Function*/
    void set_port(short const p_port);
  };
}

#endif // DIGITAL_CLASS_H
