#include "robot/devices/timer_class.hpp"

Timer::Timer():m_average_lap_vector(10,0){

}

int Timer::get_absolute_time(){
  return pros::millis();
}

int Timer::get_elapsed_time(){
  m_current_time = get_absolute_time();
  return m_current_time - m_reset_time;
}

int Timer::get_current_lap_time(){
  m_current_time = get_absolute_time();
  int l_lap_time = m_current_time - m_previous_lap_time;
  m_previous_lap_time = m_current_time;

  std::vector<int> l_temp{
    m_average_lap_vector.at(1),
    m_average_lap_vector.at(2),
    m_average_lap_vector.at(3),
    m_average_lap_vector.at(4),
    m_average_lap_vector.at(5),
    m_average_lap_vector.at(6),
    m_average_lap_vector.at(7),
    m_average_lap_vector.at(8),
    m_average_lap_vector.at(9),
    l_lap_time
  };
  m_average_lap_vector = l_temp;

  return l_lap_time;
}

double Timer::get_average_lap_time(){
  int l_sum = 0;

  for(int x = 0; x < 10; x++){
    l_sum += m_average_lap_vector.at(x);
  }
  return l_sum/10.0;
}

bool Timer::get_preform_action(){
  return false;
}

void Timer::reset_timer(){
  m_reset_time = pros::millis();
  m_action_flag = INT_MAX;
}

void Timer::stop_timer(){

}

void Timer::resume_timer(){

}
