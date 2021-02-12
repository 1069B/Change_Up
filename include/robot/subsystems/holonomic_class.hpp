#include "robot/robot_main.hpp"

#ifndef BASE_CLASS_H
#define BASE_CLASS_H

struct Trajectory{
public:
  double m_orientation_velocity;
  double m_translation_velocity;
  double m_translation_angle;
};

struct Holonomic_Motors{
public:
  double m_front_left;
  double m_front_right;
  double m_back_left;
  double m_back_right;
};

struct Acceleration{
public:
  double m_coefficient_A = 201;
	double m_coefficient_B = 5;
	double m_coefficient_C = 0.05;
	double m_coefficient_H = -27;
};

class Holonomic{
private:
  std::string m_name = "Holonomic Base";
  Robot &m_robot;

  Motor& m_front_left_motor;
  Motor& m_front_right_motor;
  Motor& m_back_left_motor;
  Motor& m_back_right_motor;

  Holonomic_Motors m_desired_velocities;
  Trajectory m_desired_trajectory;
  // Trajectory m_desired_trajectory{};
  // 

  Acceleration m_acceleration_coefficients{};

  // pros::motor_brake_mode_e m_brakeMode = pros::E_MOTOR_BRAKE_COAST;

  void autonomous();
public:
  Holonomic(Robot &p_robot);

  /* Getter Functions */
  //get

  /* Setter Functions */

  /* Action Functions */
  double speed_up(int p_controllerValue);

  void base_set_vector(double p_translational_velocity, double p_orientation, double p_turning_velocity);

  int task();

};

#endif // BASE_CLASS_H
