#include "robot/robot_main.hpp"

#ifndef BASE_CLASS_H
#define BASE_CLASS_H

struct Trajectory{
public:
  double m_orientation_velocity;
  double m_translation_velocity;
  double m_translation_angle;
  double m_duration;

  double m_x_position;
  double m_y_position;
  double m_orientation;

};


class Holonomic{
private:
  std::string m_name = "Holonomic Base";
  Robot &m_robot;

  Motor& m_front_left_motor;
  Motor& m_front_right_motor;
  Motor& m_back_left_motor;
  Motor& m_back_right_motor;

  double m_Kp = 0.002;
  double m_Ki = 0;
  double m_Kd = 0;

  bool m_movement_complete = true;

  Timer& m_timer;

  Trajectory m_desired_trajectory;

  Autonomous_Base_Status m_status;

  void driver_control();

  void autonomous();
public:
  Holonomic(Robot &p_robot);

  /* Getter Functions */
  bool get_movement_complete(){ return m_movement_complete; }

  /* Setter Functions */

  /* Action Functions */
  void initialize();

  int task();

  /* Autonomous Functions */
  void set_base_movement(double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration);

  void set_base_movement(Autonomous_Base_Status p_base_status, double p_delay, double p_x_position, double p_y_position, double p_orientation);

};

#endif // BASE_CLASS_H
