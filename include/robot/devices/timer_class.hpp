#include "main.h"

#ifndef TIMER_CLASS_H
#define TIMER_CLASS_H

class Timer{
private:
  int m_current_time{0};
  int m_reset_time{0};
  int m_previous_lap_time{0};

  std::vector<int> m_average_lap_vector;

  int m_action_flag{INT_MAX};
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
  void set_timer(int const p_timer){ m_reset_time -= pros::millis() - p_timer; };// 5000 to 2000 or 5000 to 2000

  void set_flag_delay(int const p_delay){ m_action_flag = get_absolute_time() + p_delay; };// In 100ms return get preform action true

  void set_flag_absolute_time(int const p_absolute_time){ m_action_flag = p_absolute_time; };// At time 1500 return true for get_preform action

  void set_flag_elapsed_time(int const p_elapsed_time){ m_action_flag = get_elapsed_time() + m_reset_time; };

  /*  Action Functions */
  void reset_timer();

  void stop_timer();

  void resume_timer();
};

#endif // TIMER_CLASS_H
