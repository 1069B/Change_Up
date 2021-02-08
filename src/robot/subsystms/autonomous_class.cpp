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

/* Old Auto Code */
// void Autonomous::start_auton(){
//   m_base_timer.reset_timer();
//   m_ball_timer.reset_timer();
// }

// void Autonomous::move_base(double p_start_time, double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration){
//   m_translational_velocity = p_translational_velocity;
//   m_orientation = p_orientation;
//   m_turning_velocity = p_turning_velocity;
//   m_duration = p_duration;

//   m_base_timer.set_flag_elapsed_time(p_start_time);
//   while(!m_base_timer.get_preform_action()){
//     pros::delay(5);
//   }

//   m_front_left_motor.set_desired_velocity(cos((m_orientation/180.0*M_PI) + (M_PI/4.0)) * m_translational_velocity - m_turning_velocity);
//   m_front_right_motor.set_desired_velocity(sin((m_orientation/180.0*M_PI) + (M_PI/4.0)) * m_translational_velocity + m_turning_velocity);
//   m_back_left_motor.set_desired_velocity(sin((m_orientation/180.0*M_PI) + (M_PI/4.0)) * m_translational_velocity - m_turning_velocity);
//   m_back_right_motor.set_desired_velocity(cos((m_orientation/180.0*M_PI) + (M_PI/4.0)) * m_translational_velocity + m_turning_velocity);
//   m_base_timer.set_flag_delay(p_duration);

//   while(!m_base_timer.get_preform_action()){
//     pros::delay(5);
//   }
//   m_front_left_motor.set_desired_velocity(0);
//   m_front_right_motor.set_desired_velocity(0);
//   m_back_left_motor.set_desired_velocity(0);
//   m_back_right_motor.set_desired_velocity(0);
// }

// void Autonomous::stop_base(double p_start_time){
//   m_base_timer.set_flag_elapsed_time(p_start_time);
//   while(!m_base_timer.get_preform_action()){
//     pros::delay(5);
//   }

//   m_front_left_motor.set_desired_velocity(0);
//   m_front_right_motor.set_desired_velocity(0);
//   m_back_left_motor.set_desired_velocity(0);
//   m_back_right_motor.set_desired_velocity(0);
// }

// void Autonomous::move_balls(double p_start_time, double p_intake_speed, double p_intial_roller_speed, double p_second_roller_speed, double p_duration){
//   m_ball_timer.set_flag_elapsed_time(p_start_time);
//   while(!m_ball_timer.get_preform_action()){
//     pros::delay(5);
//   }

//   left_intake.set_desired_velocity(p_intake_speed);
//   right_intake.set_desired_velocity(p_intake_speed);
//   intial_roller.set_desired_velocity(p_intial_roller_speed);
//   second_roller.set_desired_velocity(p_second_roller_speed);
//   m_ball_timer.set_flag_delay(p_duration);

//   while(!m_ball_timer.get_preform_action()){
//     pros::delay(5);
//   }
//   left_intake.set_desired_velocity(0);
//   right_intake.set_desired_velocity(0);
//   intial_roller.set_desired_velocity(0);
//   second_roller.set_desired_velocity(0);
// }

// void Autonomous::turn_intakes_on(double p_intake_speed){
//   left_intake.set_desired_velocity(p_intake_speed);
//   right_intake.set_desired_velocity(p_intake_speed);
// }

// void Autonomous::turn_intakes_off(){
//   left_intake.set_desired_velocity(0);
//   right_intake.set_desired_velocity(0);
// }

// void Autonomous::turn_intial_roller_on(double p_intake_speed){
//   intial_roller.set_desired_velocity(p_intake_speed);
// }

// void Autonomous::turn_intial_roller_off(){
//   intial_roller.set_desired_velocity(0);
// }