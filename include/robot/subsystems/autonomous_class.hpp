#include "robot/robot_main.hpp"
#include "robot/devices/timer_class.hpp"

#ifndef AUTONOMOUS_CLASS_H
#define AUTONOMOUS_CLASS_H

class Autonomous{
private:
  Robot& m_robot;

  Motor& m_front_left_motor;
	Motor& m_front_right_motor;
	Motor& m_back_left_motor;
	Motor& m_back_right_motor;

	Motor& left_intake;
	Motor& right_intake;

	Motor& intial_roller;
	Motor& second_roller;

  double m_translational_velocity;
  double m_orientation;
  double m_turning_velocity;
  double m_duration;

  Timer m_base_timer;
  Timer m_ball_timer;

public:
  Autonomous(Robot& p_robot);

  void start_auton();

  void move_base(double p_start_time, double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration);

  void stop_base(double p_start_time);

  void turn_intakes_on(double p_intake_speed);

  void turn_intakes_off();

  void turn_intial_roller_on(double p_intake_speed);

  void turn_intial_roller_off();

  void move_balls(double p_start_time, double p_intake_speed, double p_intial_roller_speed, double p_second_roller_speed, double p_duration);
};



#endif // AUTONOMOUS_CLASS_H
