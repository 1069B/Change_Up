#include "robot/robot_main.hpp"

#ifndef MOTOR_CLASS_H
#define MOTOR_CLASS_H

enum Motor_Mode{
  MOTOR_VELOCITY_DEPENDENT = 0,
  MOTOR_VOLTAGE_DEPENDENT = 1
};

class Motor{
private:
  Robot& m_robot;

  /*Settings*/
  std::string m_name{};
  int m_port{};
  bool m_reversed{};
  pros::motor_brake_mode_e_t m_brake_mode{};
  pros::motor_gearset_e_t m_motor_gearset{};

  int m_port_temp{};
  bool m_reversed_temp{};

  int m_brake_mode_temp{};
  std::string m_brake_mode_string{};

  int m_gearset_mode_temp{};
  std::string m_gearset_mode_string{};


  Data_Storing& m_settings;

  Motor_Mode m_mode{MOTOR_VELOCITY_DEPENDENT};
  int m_desired_velocity;
  int m_desired_voltage;

  int update();

public:
  /*  Constuctors  */
  Motor(Robot &p_robot, std::string const p_name, int const p_port, pros::motor_gearset_e_t const p_motor_gearset, pros::motor_brake_mode_e_t const p_motor_brake, bool const p_reversed);

  /*  Getting Functions  */
  std::string get_name(){ return m_name; }

  int get_port(){ return m_port; }

  bool get_reversed(){ return m_reversed; }

  pros::motor_brake_mode_e_t get_brake_mode(){ return m_brake_mode; }

  pros::motor_gearset_e_t get_motor_gearset(){ return m_motor_gearset; }

  int get_actual_velocity(){return pros::c::motor_get_actual_velocity(m_port); }

  int get_actual_voltage(){ return pros::c::motor_get_voltage(m_port); }

  int get_current_draw(){ return pros::c::motor_get_current_draw(m_port); }

  int get_power(){ return pros::c::motor_get_power(m_port); }

  int get_efficiency(){ return pros::c::motor_get_efficiency(m_port); }

  int get_tempature(){ return pros::c::motor_get_temperature(m_port) ;}

  int get_direction(){ return pros::c::motor_get_direction(m_port); }// TODO: Does this return 0 when not moving

  int is_over_current(){ return pros::c::motor_is_over_current(m_port); }

  int is_over_temp(){ return pros::c::motor_is_over_temp(m_port); }

  bool is_stopped(){ return pros::c::motor_is_stopped(m_port); }

  int get_postion(){ return pros::c::motor_get_position(m_port); }

  int get_torque(){ return pros::c::motor_get_torque(m_port); }

  int get_desired_velocity(){ return m_desired_velocity; }

  int get_desired_voltage(){ return m_desired_voltage; }

  bool get_connected(){ return !(get_tempature() == 2147483647); }

  /*  Setter Function  */
  void set_port(int const p_port);

  void set_reversed(bool const p_reversed);

  void set_brake_mode(pros::motor_brake_mode_e_t p_brake_mode);

  void set_motor_gearset(pros::motor_gearset_e_t p_motor_gearset);

  void set_desired_velocity(int p_desired_velocity);

  void set_desired_voltage(int p_voltage);

  /*  Action Functions */
  void reset_position(){ pros::c::motor_tare_position(m_port); }

  void define_GUI();

};

#endif // MOTOR_CLASS_H
