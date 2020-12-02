#include "robot/robot_main.hpp"
#include "robot/devices/data_storage_class.hpp"

#ifndef ROTATION_CLASS_H
#define ROTATION_CLASS_H

namespace SENSORS{
  class Rotation{
  private:
    Robot& m_robot;

    // Settings
    std::string m_name{};
    short m_port{};
    int m_position{};
    bool m_reversed{};

    Data_Storing m_settings;

  public:
    //Constructor
   Rotation(Robot &p_robot, std::string const p_name, short const p_port, bool const p_reversed, int const p_position = 0);

    // Getting Functions
    std::string get_name(){ return m_name; }

    int get_absolute_position(){ return pros::c::rotation_get_position(m_port); }

    int get_velocity(){ return pros::c::rotation_get_velocity(m_port); }
    //^^ change to revolutions per sec ^^
    int get_relative_position(){ return pros::c::rotation_get_angle(m_port); }

    bool get_reversed(){ return m_reversed; }

    // add a ten interval running average, see timer class

    // Setter Functions
    void set_position(short const p_port, int p_position);

    void set_reversed(short const p_port);


    // Action Functions
    void reset(){ pros::c::rotation_reset(m_port); }

    void reset_position(){ pros::c::rotation_reset_position(m_port); }

    void reverse(){ pros::c::rotation_reverse(m_port); }

  };
}

#endif //ROTATION_CLASS_H
