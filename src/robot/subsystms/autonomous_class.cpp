#include "robot/robot_class.hpp"

#include "robot/devices/motor_class.hpp"
#include "robot/devices/timer_class.hpp"

#include "robot/subsystems/autonomous_class.hpp"
#include "robot/subsystems/holonomic_class.hpp"
#include "robot/subsystems/manipulator.hpp"


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


Autonomous::Autonomous(Robot& p_robot):
m_robot(p_robot),
m_base_timer(*new Timer()){

}

void Autonomous::start_autonomous(){
  m_base_timer.reset_timer();
  //m_ball_timer.reset_timer();
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
void Autonomous::manipulator_feild(double p_delay){// Moves Reds to Top and descores all blue balls
  m_robot.get_manipulator().set_mode(MANIPULATOR_FEILD);
}

void Autonomous::manipulator_score_goal(double p_delay){// Scores top red and descores
  m_robot.get_manipulator().set_mode(MANIPULATOR_GOAL_SCORE);
}

void Autonomous::manipulator_control_goal(double p_delay){// Grabs ball off feild
  m_robot.get_manipulator().set_mode(MANIPULATOR_GOAL_REMOVE);
}

/* Action Functions */
void Autonomous::task(){

}

/* Old Auto Code */
void Autonomous::move_base(double p_delay, double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration){
  m_base_timer.set_flag_delay(p_delay);
  while(!m_base_timer.get_preform_action()){
    m_robot.get_manipulator().task();
    pros::delay(5);
  }

  m_robot.get_holonomic().base_set_vector(p_translational_velocity, p_orientation, p_turning_velocity);

  m_base_timer.set_flag_delay(p_duration);

  while(!m_base_timer.get_preform_action()){
    m_robot.get_manipulator().task();
    pros::delay(5);
  }
  m_robot.get_holonomic().base_set_vector(0, 0, 0);
}

void Autonomous::delay(double p_delay){
  m_base_timer.set_flag_delay(p_delay);
  while(!m_base_timer.get_preform_action()){
    m_robot.get_manipulator().task();
    pros::delay(5);
  }
}
