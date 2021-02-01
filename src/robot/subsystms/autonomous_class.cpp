#include "robot/subsystems/autonomous_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/robot_class.hpp"



Base_Event::Base_Event(AUTONOMOUS_BASE_STATUS p_base_status, double p_delay, double p_x_position, double p_y_position, double p_orientation){
  m_base_status = p_base_status;
  m_delay = p_delay;
  m_x_position = p_x_position;
  m_y_position = p_y_position;
  m_orientation = p_orientation;
}

Manipulator_Event::Manipulator_Event(AUTONOMOUS_MANIPULATOR_STATUS p_manipulator_status, double p_delay){
  m_manipulator_status = p_manipulator_status;
  m_delay = p_delay;

}


Autonomous::Autonomous(Robot& p_robot):m_robot(p_robot){

}

void Autonomous::start_autonomous(){

}

void Autonomous::end_autonomous(){

}

/* Base Functions */
void Autonomous::base_translate_to(double p_x_position, double p_y_position, double p_delay){// Point to Point
  m_base_events.push_back(Base_Event(BASE_TRANSLATE, p_delay, p_x_position, p_y_position, INT_MIN));
}

void Autonomous::base_orientate_to(double p_orientation, double p_delay){
  m_base_events.push_back(Base_Event(BASE_ORIENTATION, p_delay, INT_MIN, INT_MIN, p_orientation));
}

void Autonomous::base_turn_to(double p_x_position, double p_y_position, double p_delay){// Arc Turn
  m_base_events.push_back(Base_Event(BASE_TURN, p_delay, p_x_position, p_y_position, INT_MIN));
}

void Autonomous::base_pose_to(double p_x_position, double p_y_position, double p_orientation, double p_delay){// Point to Point with Orientation Change
  m_base_events.push_back(Base_Event(BASE_POSE, p_delay, p_x_position, p_y_position, p_orientation));
}

void Autonomous::base_align_to_goal(double p_delay){
  m_base_events.push_back(Base_Event(BASE_POSE, p_delay, INT_MIN, INT_MIN, INT_MIN));
}

/* Manipulator Functions */
void Autonomous::preset_balls(double p_delay){// Moves Reds to Top and descores all blue balls
  m_manipulator_events.push_back(Manipulator_Event(INTAKE_PRESET_BALLS, p_delay));
}

void Autonomous::control_goal(double p_delay){// Scores top red and descores
  m_manipulator_events.push_back(Manipulator_Event(INTAKE_CONTROL_GOAL, p_delay));
}

void Autonomous::grab_ball(double p_delay){// Grabs ball off feild
  m_manipulator_events.push_back(Manipulator_Event(INTAKE_GRAB_BALL, p_delay));
}

/* Action Functions */
void Autonomous::task(){

}