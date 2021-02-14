#include "robot/robot_main.hpp"

#ifndef AUTONOMOUS_CLASS_H
#define AUTONOMOUS_CLASS_H

#define NO_DELAY 0

enum AUTONOMOUS_BASE_STATUS{
  BASE_TRANSLATE,
  BASE_ORIENTATION,
  BASE_TURN,
  BASE_POSE,
  BASE_ALIGN_GOAL,
  BASE_STATIONARY
};

enum AUTONOMOUS_MANIPULATOR_STATUS{
  AUTONOMOUS_INTAKE_PRESET_BALLS,
  AUTONOMOUS_INTAKE_CONTROL_GOAL,
  AUTONOMOUS_INTAKE_GRAB_BALL,
  AUTONOMOUS_INTAKE_STATIONARY
};

struct Base_Event{
public:
  AUTONOMOUS_BASE_STATUS m_base_status;
  double m_delay;
  double m_x_position;
  double m_y_position;
  double m_orientation;

  Base_Event(AUTONOMOUS_BASE_STATUS p_base_status, double p_delay, double p_x_position, double p_y_position, double p_orientation);
};

struct Manipulator_Event{
public:
  AUTONOMOUS_MANIPULATOR_STATUS m_manipulator_status;
  double m_delay;

  Manipulator_Event(AUTONOMOUS_MANIPULATOR_STATUS p_base_status, double p_delay);
};

class Autonomous{
private:
  Robot& m_robot;

  std::vector<Base_Event> m_base_events;
  std::vector<Manipulator_Event> m_manipulator_events;

  Timer& m_base_timer;

public:
  Autonomous(Robot& m_robot);

  void start_autonomous();

  void end_autonomous();

  /* Base Functions */
  void base_translate_to(double p_x_position, double p_y_position, double p_delay = NO_DELAY);// Point to Point

  void base_orientate_to(double p_orientation, double p_delay = NO_DELAY);// Point Rotation

  void base_turn_to(double p_x_position, double p_y_position, double p_delay = NO_DELAY);// Arc Turn

  void base_pose_to(double p_x_position, double p_y_position, double p_orientation, double p_delay = NO_DELAY);// Point to Point with Orientation Change

  void base_align_to_goal(double p_delay = NO_DELAY);

  /* Manipulator Functions */
  void manipulator_feild(Manipulator_Intake_Mode p_intake_mode, double p_delay = NO_DELAY);// Picks balls up off feild

  void manipulator_score(Manipulator_Intake_Mode p_intake_mode,double p_delay = NO_DELAY);// Scores top red

  /* Action Functions */
  void task();

  /*Old Functions*/
  void move_base(double p_start_time, double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration);

  void delay(double p_delay);
};

#endif // AUTONOMOUS_CLASS_H
