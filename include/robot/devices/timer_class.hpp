#include "robot/robot_main.hpp"

#ifndef TIMER_CLASS_H
#define TIMER_CLASS_H

class Timer{
private:
  int m_current_time{0};
  int m_reset_time{0};
  int m_previous_lap_time{0};

  std::vector<int> m_average_lap_vector;

  int m_action_flag{INT_MAX};

  bool m_stopped{false};
  int m_stop_time{0};
public:
  /*  Constuctors  */
  Timer();
  /*  Getting Function  */
  int get_absolute_time();

  int get_elapsed_time();

  int get_current_lap_time();

  double get_average_lap_time();// Last 10 laps

  bool get_preform_action();

  /*  Setter Function  */
  void set_timer(int const p_timer){ m_reset_time -= get_absolute_time() - p_timer; };

  void set_flag_delay(int const p_delay){ m_action_flag = get_absolute_time() + p_delay; };

  void set_flag_absolute_time(int const p_absolute_time_flag){ m_action_flag = p_absolute_time_flag; };

  void set_flag_elapsed_time(int const p_elapsed_time_flag){ set_flag_delay(p_elapsed_time_flag - get_elapsed_time()); };

  /*  Action Functions */
  void reset_timer();

  void stop_timer();

  void resume_timer();
};

#endif // TIMER_CLASS_H
