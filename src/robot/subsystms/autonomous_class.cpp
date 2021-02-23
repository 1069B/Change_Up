#include "robot/robot_class.hpp"

#include "robot/devices/motor_class.hpp"
#include "robot/devices/timer_class.hpp"

#include "robot/subsystems/holonomic_class.hpp"
#include "robot/subsystems/manipulator.hpp"
#include "robot/subsystems/autonomous_class.hpp"
#include "robot/subsystems/autonomous_rountines_class.hpp"

Autonomous::Autonomous(Robot& p_robot):
m_robot(p_robot){}

void Autonomous::set_selected_routine(std::string p_routine_name){
    for(auto x : m_routines){
        if(x->get_name() == p_routine_name)
        m_selected_routine = x;
    }
}

Autonomous_Routine& Autonomous::add_autonomous_routine(std::string p_routine_name, Robot_Alliance p_routine_alliance){
  for(auto x : m_routines){
    if(x->get_name() == p_routine_name)
      return *x;
  }

  Autonomous_Routine* l_new_routine{new Autonomous_Routine(*this, p_routine_name, p_routine_alliance)};
  m_routines.push_back(l_new_routine);
  return *l_new_routine;
}

bool Autonomous::is_running(){
    if(m_selected_routine == NULL)
        return false;

    return m_selected_routine->m_running_autonomous; 
}

void Autonomous::task(){
    if(m_selected_routine == NULL)
        return;
    m_selected_routine->task();   
}

void Autonomous::start_autonomous(){
    if(m_selected_routine == NULL)
        return;
    m_selected_routine->start_autonomous();
}

void Autonomous::end_autonomous(){
    if(m_selected_routine == NULL)
        return;
    m_selected_routine->end_autonomous();
}

void Autonomous::define_GUI(){

}