#include "robot/robot_main.hpp"

#ifndef AUTONOMOUS_CLASS_H
#define AUTONOMOUS_CLASS_H

#define NO_DELAY 0

class Autonomous{
private:
  Robot& m_robot;

  double m_gui_selected_program = -1;

  std::vector<Autonomous_Routine*> m_routines;
  Autonomous_Routine* m_selected_routine;

	friend class Autonomous_Routine;
public:
  /* Constrotors */
  Autonomous(Robot& p_robot);

  /*Getter Functions*/
  Autonomous_Routine& add_autonomous_routine(std::string p_routine_name, Robot_Alliance p_routine_alliance);

  void set_selected_program(double p_program);

  int set_blue_1();

  void set_selected_routine(std::string p_routine_name);
  void set_selected_routine(Autonomous_Routine& p_routine){ m_selected_routine = &p_routine; }

  

  bool is_running();

  void task();

  void start_autonomous();

  void end_autonomous();

  void define_GUI();
};

#endif // AUTONOMOUS_CLASS_H