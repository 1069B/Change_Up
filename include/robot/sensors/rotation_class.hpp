#include "robot/robot_main.hpp"

#ifndef ROTATION_CLASS_H
#define ROTATION_CLASS_H

namespace SENSOR{
  class Rotation{
  private:
    Robot& m_robot;

    std::string m_name{};
    short m_port{};
    int m_position_offset{};
    bool m_reversed{};

    Data_Storing& m_settings;

    std::vector<double> m_average_velocity_vector;

  public:
    Rotation(Robot &p_robot, std::string const p_name, short const p_port, bool const p_reversed, int const p_position_offset = 0);

    /* Getter Functions */
    std::string get_name(){ return m_name; }

    double get_absolute_position(){ return (double)pros::c::rotation_get_position(m_port)/36000.0; }

    double get_relative_position(){ return (double)pros::c::rotation_get_angle(m_port)/36000.0; }

    double get_velocity();

    bool get_reversed(){ return m_reversed; }

    double get_running_average_velocity();

    int get_port(){ return m_port; }

    /* Setter Functions */
    void set_position_offset(int const p_position_offset);

    void set_reversed(bool const p_reversed);

    void set_port(int const p_port);

    // Action Functions
    void reset(){ pros::c::rotation_reset(m_port); }

    void reset_position(){ pros::c::rotation_reset_position(m_port); }

    void reverse(){ pros::c::rotation_reverse(m_port); }
  };
}

#endif //ROTATION_CLASS_H
