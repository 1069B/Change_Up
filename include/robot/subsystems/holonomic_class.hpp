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

  /* Orientation PID */
  double m_orientation_error;
  double m_orientation_previous_error;
  double m_orientation_integral;
  double m_orientation_derivative;

  double m_Kp_orientation = 2.8;
  double m_Ki_orientation = 0.015;
  double m_Kd_orientation = 0.8;

  Timer& m_movement_timer;
  bool m_movement_ending = false;

  bool m_movement_complete = true;

  Timer& m_timer;

  pros::Vision vision_sensor{4};

  pros::vision_signature_s_t Goal_Sig = pros::Vision::signature_from_utility(1, -5319, -4815, -5067, -6281, -5685, -5983, 5.000, 0);

  double m_goal_x_position;
  double m_goal_y_position;

  double m_goal_width;
  double m_goal_hight;

  bool m_goal = false;

  Trajectory m_desired_trajectory;

  Autonomous_Base_Status m_status;

  void vision_based_goal();

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

  void define_GUI();

  /* Autonomous Functions */
  void set_base_movement(double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration);

  void set_base_movement(Autonomous_Base_Status p_base_status, double p_delay, double p_x_position, double p_y_position, double p_orientation);

  void set_base_vision_movement(Autonomous_Base_Status p_base_status, double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration);

};

#endif // BASE_CLASS_H
