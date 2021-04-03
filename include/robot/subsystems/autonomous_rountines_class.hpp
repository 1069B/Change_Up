#include "robot/robot_main.hpp"

#ifndef AUTONOMOUS_ROUTINES_CLASS_H
#define AUTONOMOUS_ROUTINES_CLASS_H

#define NO_DELAY 0

struct Base_Event{
private:
  Autonomous_Base_Status m_base_status;
  double m_delay;
  double m_x_position;
  double m_y_position;
  double m_orientation;

  /*Temp*/
  double m_translational_velocity;
  double m_turning_velocity;
  double m_duration;

  friend class Autonomous_Routine;
  friend class Robot_Event;

  Base_Event(Autonomous_Base_Status p_base_status, double p_delay, double p_x_position, double p_y_position, double p_orientation);

  Base_Event(Autonomous_Base_Status p_base_status, double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration, double p_delay);

public:
  static Base_Event& base_move(double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration, double p_delay = NO_DELAY);// Point to Point
  //  static Base_Event base_translate_to(double p_x_position, double p_y_position, double p_delay = NO_DELAY);// Point to Point

  static Base_Event& base_orientate_to(double p_orientation, double p_delay = NO_DELAY);// Point Rotation

  // static Base_Event base_turn_to(double p_x_position, double p_y_position, double p_delay = NO_DELAY);// Arc Turn

  // static Base_Event base_pose_to(double p_x_position, double p_y_position, double p_orientation, double p_delay = NO_DELAY);// Point to Point with Orientation Change

  static Base_Event& base_align_to_goal(double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration, double p_delay = NO_DELAY);

  static Base_Event& base_stationary(double p_duration, double p_delay = NO_DELAY);
};
struct Intake_Event{
private:
  Autonomous_Intake_Status m_intake_status;
  Intake_Retract_Mode m_intake_retract;
  double m_delay;

  friend class Autonomous_Routine;
  friend class Robot_Event;

  Intake_Event(Autonomous_Intake_Status p_intake_status, Intake_Retract_Mode p_intake_retract, double p_delay);
  
public:
  static Intake_Event& intake_store(double p_delay = NO_DELAY);

  static Intake_Event& intake_goal(double p_delay = NO_DELAY);

  static Intake_Event& intake_grab(Intake_Retract_Mode p_intake_retract, double p_delay = NO_DELAY);

  static Intake_Event& intake_manual(double p_delay = NO_DELAY);

  static Intake_Event& intake_stationary(double p_delay = NO_DELAY);
};
struct Lift_Event{
private:
  Autonomous_Lift_Status m_lift_status;
  double m_delay;

  friend class Autonomous_Routine;
  friend class Robot_Event;

  Lift_Event(Autonomous_Lift_Status p_lift_status, double p_delay);
public:
  static Lift_Event& lift_score_one(double p_delay = NO_DELAY);

  static Lift_Event& lift_score_all(double p_delay = NO_DELAY);

  static Lift_Event& lift_sort(double p_delay = NO_DELAY);

  static Lift_Event& lift_sort_and_shoot(double p_delay = NO_DELAY);

  static Lift_Event& lift_stationary(double p_delay = NO_DELAY);
};

struct Robot_Event{
  Base_Event& m_base_event;
  Intake_Event& m_intake_event;
  Lift_Event& m_lift_event;

  Robot_Event(Base_Event& p_base_event, Intake_Event& p_intake_event, Lift_Event& p_lift_event);
};

class Autonomous_Routine{
private:
  Robot& m_robot;
  Autonomous& m_autonomous;

  std::string m_routine_name;
  Robot_Alliance m_routine_alliance;

  std::vector<Robot_Event*> m_autonomous_events;

  Timer& m_base_timer;
  Timer& m_lift_timer;
  Timer& m_intake_timer;
  
  bool m_running_autonomous = false;
  int m_current_event = 0;
  int m_previous_event = -1;

  friend class Autonomous;
public:
  /* Constrotors */
  Autonomous_Routine(Autonomous& p_autonomous, std::string p_routine_name, Robot_Alliance p_routine_alliance);

  /*Getter Functions*/
  std::string get_name(){ return m_routine_name; }

  /*Robot Functions*/
  void add_robot_event(Base_Event& p_base_event, Intake_Event& p_intake_event, Lift_Event& p_lift_event);

  void task();

  void start_autonomous();

  void end_autonomous();
};

#endif // AUTONOMOUS_ROUTINES_CLASS_H