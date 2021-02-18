#include "robot/robot_main.hpp"

#ifndef AUTONOMOUS_CLASS_H
#define AUTONOMOUS_CLASS_H

#define NO_DELAY 0

enum Autonomous_Base_Status{
  BASE_TRANSLATE,
  BASE_ORIENTATION,
  BASE_TURN,
  BASE_POSE,
  BASE_ALIGN_GOAL,
  BASE_STATIONARY
};

enum Autonomous_Intake_Status{
  AUTONOMOUS_INTAKE_GRAB,
  AUTONOMOUS_INTAKE_GOAL,
  AUTONOMOUS_INTAKE_STORE,
  AUTONOMOUS_INTAKE_STATIONARY
};

enum Autonomous_Lift_Status{
  AUTONOMOUS_LIFT_SORT,
  AUTONOMOUS_LIFT_SCORE,
  AUTONOMOUS_LIFT_STATIONARY
};

struct Base_Event{
private:
  Autonomous_Base_Status m_base_status;
  double m_delay;
  double m_x_position;
  double m_y_position;
  double m_orientation;

  friend class Autonomous_Routine;

  Base_Event(Autonomous_Base_Status p_base_status, double p_delay, double p_x_position, double p_y_position, double p_orientation);
public:
  static Base_Event base_translate_to(double p_x_position, double p_y_position, double p_delay = NO_DELAY);// Point to Point

  static Base_Event base_orientate_to(double p_orientation, double p_delay = NO_DELAY);// Point Rotation

  static Base_Event base_turn_to(double p_x_position, double p_y_position, double p_delay = NO_DELAY);// Arc Turn

  static Base_Event base_pose_to(double p_x_position, double p_y_position, double p_orientation, double p_delay = NO_DELAY);// Point to Point with Orientation Change

  static Base_Event base_align_to_goal(double p_delay = NO_DELAY);

  static Base_Event base_stationary(double p_duration);
};
struct Intake_Event{
private:
  Autonomous_Intake_Status m_intake_status;
  Intake_Retract_Mode m_intake_retract;
  double m_delay;

  friend class Autonomous_Routine;

  Intake_Event(Autonomous_Intake_Status p_intake_status, Intake_Retract_Mode p_intake_retract, double p_delay);
  
public:
  static Intake_Event intake_store(double p_delay = NO_DELAY);

  static Intake_Event intake_goal(double p_delay = NO_DELAY);

  static Intake_Event intake_grab(Intake_Retract_Mode p_intake_retract, double p_delay = NO_DELAY);

  static Intake_Event intake_stationary(double p_delay = NO_DELAY);
};
struct Lift_Event{
private:
  Autonomous_Lift_Status m_lift_status;
  double m_delay;

  friend class Autonomous_Routine;

  Lift_Event(Autonomous_Lift_Status p_lift_status, double p_delay);
public:
  static Lift_Event lift_score(double p_delay = NO_DELAY);

  static Lift_Event lift_sort(double p_delay = NO_DELAY);

  static Lift_Event lift_stationary(double p_delay = NO_DELAY);
};

struct Robot_Event{
  Base_Event m_base_event;
  Intake_Event m_intake_event;
  Lift_Event m_lift_event;

  Robot_Event(Base_Event p_base_event, Intake_Event p_intake_event, Lift_Event p_lift_event);
};

class Autonomous_Routine{
private:
  Robot& m_robot;

  std::string m_routine_name;
  Robot_Alliance m_routine_alliance;

  std::vector<Robot_Event> m_autonomous_events;

  Timer& m_base_timer;
  Timer& m_lift_timer;
  Timer& m_intake_timer;

  static std::vector<Autonomous_Routine*> m_routines;
  static Autonomous_Routine* m_selected_routine;

public:
  /* Constrotors */
  Autonomous_Routine(Robot& p_robot, std::string p_routine_name, Robot_Alliance p_routine_alliance);

  /*Getter Functions*/
  std::string get_name(){ return m_routine_name; }

  void start_autonomous();

  void end_autonomous();

  /*Robot Functions*/
  void add_robot_event(Base_Event p_base_event, Intake_Event p_intake_event, Lift_Event p_lift_event);

  static void set_selected_routine(std::string p_routine_name);

  static void task();
};

#endif // AUTONOMOUS_CLASS_H
