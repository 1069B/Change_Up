#include "robot/subsystems/autonomous_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/robot_class.hpp"

Autonomous::Autonomous(Robot& p_robot):m_robot(p_robot),
m_front_left_motor(m_robot.find_motor("Front Left Base")),
m_front_right_motor(m_robot.find_motor("Front Right Base")),
m_back_left_motor(m_robot.find_motor("Back Left Base")),
m_back_right_motor(m_robot.find_motor("Back Right Base")),
left_intake(m_robot.find_motor("Left Intake")),
right_intake(m_robot.find_motor("Right Intake")),
intial_roller(m_robot.find_motor("Intial Rollers")),
second_roller(m_robot.find_motor("Second Rollers")){

}

void Autonomous::start_auton(){
  m_base_timer.reset_timer();
  m_ball_timer.reset_timer();
}

void Autonomous::move_base(double p_start_time, double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration){
  m_translational_velocity = p_translational_velocity;
  m_orientation = p_orientation;
  m_turning_velocity = p_turning_velocity;
  m_duration = p_duration;

  m_base_timer.set_flag_elapsed_time(p_start_time);
  while(!m_base_timer.get_preform_action()){
    pros::delay(5);
  }

  m_front_left_motor.set_desired_velocity(cos((m_orientation/180.0*M_PI) + (M_PI/4.0)) * m_translational_velocity - m_turning_velocity);
  m_front_right_motor.set_desired_velocity(sin((m_orientation/180.0*M_PI) + (M_PI/4.0)) * m_translational_velocity + m_turning_velocity);
  m_back_left_motor.set_desired_velocity(sin((m_orientation/180.0*M_PI) + (M_PI/4.0)) * m_translational_velocity - m_turning_velocity);
  m_back_right_motor.set_desired_velocity(cos((m_orientation/180.0*M_PI) + (M_PI/4.0)) * m_translational_velocity + m_turning_velocity);
  m_base_timer.set_flag_delay(p_duration);

  while(!m_base_timer.get_preform_action()){
    pros::delay(5);
  }
  m_front_left_motor.set_desired_velocity(0);
  m_front_right_motor.set_desired_velocity(0);
  m_back_left_motor.set_desired_velocity(0);
  m_back_right_motor.set_desired_velocity(0);
}

void Autonomous::stop_base(double p_start_time){
  m_base_timer.set_flag_elapsed_time(p_start_time);
  while(!m_base_timer.get_preform_action()){
    pros::delay(5);
  }

  m_front_left_motor.set_desired_velocity(0);
  m_front_right_motor.set_desired_velocity(0);
  m_back_left_motor.set_desired_velocity(0);
  m_back_right_motor.set_desired_velocity(0);
}

void Autonomous::move_balls(double p_start_time, double p_intake_speed, double p_intial_roller_speed, double p_second_roller_speed, double p_duration){
  m_ball_timer.set_flag_elapsed_time(p_start_time);
  while(!m_ball_timer.get_preform_action()){
    pros::delay(5);
  }

  left_intake.set_desired_velocity(p_intake_speed);
  right_intake.set_desired_velocity(p_intake_speed);
  intial_roller.set_desired_velocity(p_intial_roller_speed);
  second_roller.set_desired_velocity(p_second_roller_speed);
  m_ball_timer.set_flag_delay(p_duration);

  while(!m_ball_timer.get_preform_action()){
    pros::delay(5);
  }
  left_intake.set_desired_velocity(0);
  right_intake.set_desired_velocity(0);
  intial_roller.set_desired_velocity(0);
  second_roller.set_desired_velocity(0);
}

void Autonomous::turn_intakes_on(double p_intake_speed){
  left_intake.set_desired_velocity(p_intake_speed);
  right_intake.set_desired_velocity(p_intake_speed);
}

void Autonomous::turn_intakes_off(){
  left_intake.set_desired_velocity(0);
  right_intake.set_desired_velocity(0);
}

void Autonomous::turn_intial_roller_on(double p_intake_speed){
  intial_roller.set_desired_velocity(p_intake_speed);
}

void Autonomous::turn_intial_roller_off(){
  intial_roller.set_desired_velocity(0);
}
