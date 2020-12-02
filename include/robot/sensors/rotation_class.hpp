#include "robot/robot_main.hpp"
#include "robot/devices/data_storage_class.hpp"

#ifndef ROTATION_CLASS_H
#define ROTATION_CLASS_H

/*enum {

};*/

class Robot{
private:
  short m_port{};
  int m_position{};

  Data_Storing m_settings;

public:
  //Constructor
  Rotation(Robot &p_robot, short const p_port, int const p_position);

  // Getting Functions
 int rotation_get_position(){return pros::c::get_target_}

  // Setter Functions

  // Action Functions
}
