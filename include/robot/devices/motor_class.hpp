#include "robot/robot_main.hpp"
#include "robot/devices/data_storage_class.hpp"

#ifndef MOTOR_CLASS_H
#define MOTOR_CLASS_H

class Motor{
private:
  Robot &m_robot;

  /*Settings*/
  std::string m_name{};
  short m_port{};
  bool m_reversed{};
  pros::motor_brake_mode_e_t m_brake_mode{};
  pros::motor_gearset_e_t m_motor_gearset{};

  Data_Storing m_settings{"Settings.xml", "Motors", m_name};

  int m_desired_velocity;

  int m_desired_voltage;

  int m_velocity;

  int m_zero_position;

  int m_tempature;

  int m_torque;
public:
  /*  Constuctors  */
  Motor(Robot &p_robot, std::string const p_name, short const p_port, pros::motor_gearset_e_t const m_motor_gearset, bool const m_reversed);
  /*  Getting Function  */
  std::string get_name(){ return m_name; };
  /*  Setter Function  */

  /*  Action Functions */

};


#endif // MOTOR_CLASS_H
