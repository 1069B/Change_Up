#include "robot/robot_class.hpp"

#include "robot/devices/motor_class.hpp"
#include "robot/devices/timer_class.hpp"

#include "robot/subsystems/autonomous_class.hpp"
#include "robot/subsystems/holonomic_class.hpp"
#include "robot/subsystems/manipulator.hpp"

/* Base Functions */
Base_Event::Base_Event(Autonomous_Base_Status p_base_status, double p_delay, double p_x_position, double p_y_position, double p_orientation){
  m_base_status = p_base_status;
  m_delay = p_delay;
  m_x_position = p_x_position;
  m_y_position = p_y_position;
  m_orientation = p_orientation;
}

Base_Event Base_Event::base_translate_to(double p_x_position, double p_y_position, double p_delay){// Point to Point
  return Base_Event(BASE_TRANSLATE, p_delay, p_x_position, p_y_position, INT_MIN);
}

Base_Event Base_Event::base_orientate_to(double p_orientation, double p_delay){// Point Rotation
  return Base_Event(BASE_ORIENTATION, p_delay, INT_MIN, INT_MIN, p_orientation);
}

Base_Event Base_Event::base_turn_to(double p_x_position, double p_y_position, double p_delay){// Arc Turn
  return Base_Event(BASE_TURN, p_delay, p_x_position, p_y_position, INT_MIN);
}

Base_Event Base_Event::base_pose_to(double p_x_position, double p_y_position, double p_orientation, double p_delay){// Point to Point with Orientation Change
  return Base_Event(BASE_POSE, p_delay, p_x_position, p_y_position, p_orientation);
}

Base_Event Base_Event::base_align_to_goal(double p_delay){
  return Base_Event(BASE_POSE, p_delay, INT_MIN, INT_MIN, INT_MIN);
}

Base_Event Base_Event::base_stationary(double p_duration){
  return Base_Event(BASE_STATIONARY, p_duration, INT_MIN, INT_MIN, INT_MIN);
}

/* Intake Functions */
Intake_Event::Intake_Event(Autonomous_Intake_Status p_intake_status, double p_delay){
  m_intake_status = p_intake_status;
  m_delay = p_delay;
}
  
Intake_Event Intake_Event::intake_store(double p_delay){
  return Intake_Event(AUTONOMOUS_INTAKE_STORE, p_delay);
}

Intake_Event Intake_Event::intake_goal(double p_delay){
  return Intake_Event(AUTONOMOUS_INTAKE_GOAL, p_delay);
}

Intake_Event Intake_Event::intake_grab(double p_delay){
  return Intake_Event(AUTONOMOUS_INTAKE_GRAB, p_delay);
}

Intake_Event Intake_Event::intake_stationary(double p_delay){
  return Intake_Event(AUTONOMOUS_INTAKE_STATIONARY, p_delay);
}

/* Lift Functions */
Lift_Event::Lift_Event(Autonomous_Lift_Status p_lift_status, double p_delay){
  m_lift_status = p_lift_status;
  m_delay = p_delay;
}

Lift_Event Lift_Event::lift_score(double p_delay){
  return Lift_Event(AUTONOMOUS_LIFT_SCORE, p_delay);
}

Lift_Event Lift_Event::lift_sort(double p_delay){
  return Lift_Event(AUTONOMOUS_LIFT_SORT, p_delay);
}

Lift_Event Lift_Event::lift_stationary(double p_delay){
  return Lift_Event(AUTONOMOUS_LIFT_STATIONARY, p_delay);
}


Autonomous_Routine::Autonomous_Routine(Robot& p_robot):
m_robot(p_robot),
m_base_timer(*new Timer()),
m_intake_timer(*new Timer()),
m_lift_timer(*new Timer()){

}

void Autonomous_Routine::start_autonomous(){
  m_base_timer.reset_timer();
  //m_ball_timer.reset_timer();
}

void Autonomous_Routine::end_autonomous(){

}

void Autonomous_Routine::task(){

}