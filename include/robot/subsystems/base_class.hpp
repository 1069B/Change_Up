#include "robot/robot_class.hpp"

#ifndef BASE_CLASS_H
#define BASE_CLASS_H

struct Trajectory{
public:
  double m_orientation;
  double m_velocity;
};

struct Acceleration{
public:
  double m_coeffecint_A = 201;
	double m_coeffecint_B = 5;
	double m_coeffecint_C = 0.05;
	double m_coeffecint_H = -27;
};

enum Base_State{
  BASE_STATIONARY,
  BASE_ACCELERATING,
  BASE_DEACCELERATING,
  BASE_CONSTANT_VELOCITY
};

enum Base_Mode{
  BASE_DRIVER,
  BASE_AUTON,
  BASE_INITIALIZE,
  BASE_STANDBY
};

class Base{
private:
  std::string m_name = "Base";
  Robot &m_robot;

  Motor& m_front_left_motor;
  Motor& m_front_right_motor;
  Motor& m_back_left_motor;
  Motor& m_back_right_motor;
  //Motor& m_center_motor;

  Trajectory m_desired_trajectory{};
  Trajectory m_actual_trajectory{};

  Acceleration m_acceleration_coefficents{};

  pros::motor_brake_mode_e m_brakeMode = pros::E_MOTOR_BRAKE_COAST;

public:
  Base();

  /* Getter Functions */
  //get

  /* Setter Functions */
  void set_trajectory(double h_heading, double h_velocity);

  /* Action Functions */

};

#endif // BASE_CLASS_H
