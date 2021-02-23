#include "robot/robot_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/devices/controller_class.hpp"
#include "robot/devices/timer_class.hpp"
#include "robot/subsystems/holonomic_class.hpp"


Holonomic::Holonomic(Robot &p_robot):
m_robot(p_robot),
m_front_left_motor(m_robot.add_motor("Front Left Base", 15, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false)),
m_front_right_motor(m_robot.add_motor("Front Right Base", 16, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, true)),
m_back_left_motor(m_robot.add_motor("Back Left Base", 5, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false)),
m_back_right_motor(m_robot.add_motor("Back Right Base", 6, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, true)),
m_timer(*new Timer())
{
}

void Holonomic::set_base_movement(double p_translational_velocity, double p_orientation, double p_turning_velocity, double p_duration){
  m_desired_trajectory.m_translation_velocity = p_translational_velocity;
  m_desired_trajectory.m_orientation_velocity = p_turning_velocity;
  m_desired_trajectory.m_translation_angle = p_orientation;
  m_desired_trajectory.m_duration = p_duration;

  m_timer.reset_timer();
  m_timer.set_flag_delay(m_desired_trajectory.m_duration);

  m_movement_complete = false;
}

void Holonomic::autonomous(){
  if(m_timer.get_flag_remaining() == 0){
    m_front_left_motor = 0;
    m_front_right_motor = 0;
    m_back_left_motor = 0;
    m_back_right_motor = 0;

    m_movement_complete = true;
    return;
  }

  double speed_up_coefficient = m_timer.get_elapsed_time() * m_Kp;
  double speed_down_coefficient = m_timer.get_flag_remaining() * m_Kp;

  double motor_coefficient;
  if(speed_up_coefficient < 1.0 && speed_up_coefficient < speed_down_coefficient)
    motor_coefficient = speed_up_coefficient;
  else if(speed_down_coefficient < 1.0 && speed_down_coefficient < speed_up_coefficient)
    motor_coefficient = speed_down_coefficient;
  else if(speed_up_coefficient >= 1.0 && speed_down_coefficient >= 1.0)
    motor_coefficient = 1.0;
  else
    motor_coefficient = 0;
 
  m_front_left_motor = motor_coefficient*(cos((m_desired_trajectory.m_translation_angle/180.0*M_PI) + (M_PI/4.0)) * m_desired_trajectory.m_translation_velocity - m_desired_trajectory.m_orientation_velocity);
  m_front_right_motor = motor_coefficient*(sin((m_desired_trajectory.m_translation_angle/180.0*M_PI) + (M_PI/4.0)) * m_desired_trajectory.m_translation_velocity + m_desired_trajectory.m_orientation_velocity);
  m_back_left_motor = motor_coefficient*(sin((m_desired_trajectory.m_translation_angle/180.0*M_PI) + (M_PI/4.0)) * m_desired_trajectory.m_translation_velocity - m_desired_trajectory.m_orientation_velocity);
  m_back_right_motor = motor_coefficient*(cos((m_desired_trajectory.m_translation_angle/180.0*M_PI) + (M_PI/4.0)) * m_desired_trajectory.m_translation_velocity + m_desired_trajectory.m_orientation_velocity);
}

void Holonomic::driver_control(){
  CONTROLLER::Controller& l_main_controller = m_robot.get_main_controller();
	CONTROLLER::Controller& l_partner_controller = m_robot.get_partner_controller();
  
  int l_translation_coefficient;
  int l_orientation_coefficient;
  if(l_main_controller.ButtonL2.get_state() && l_main_controller.ButtonR2.get_state()){
    l_translation_coefficient = 100;
    l_orientation_coefficient = 100;
  }
  else if(l_main_controller.ButtonL2.get_state()){
    l_translation_coefficient = 100;
    l_orientation_coefficient = 200;
  }
  else if(l_main_controller.ButtonR2.get_state()){
    l_translation_coefficient = 200;
    l_orientation_coefficient = 100;
  }
  else{
    l_translation_coefficient = 200;
    l_orientation_coefficient = 200;
  }

    m_front_left_motor.set_desired_velocity(l_translation_coefficient*l_main_controller.Axis3.get_percent()+l_translation_coefficient*l_main_controller.Axis4.get_percent()+(l_orientation_coefficient*l_main_controller.Axis1.get_percent()));
    m_front_right_motor.set_desired_velocity(l_translation_coefficient*l_main_controller.Axis3.get_percent()-l_translation_coefficient*l_main_controller.Axis4.get_percent()-(l_orientation_coefficient*l_main_controller.Axis1.get_percent()));
    m_back_left_motor.set_desired_velocity(l_translation_coefficient*l_main_controller.Axis3.get_percent()-l_translation_coefficient*l_main_controller.Axis4.get_percent()+(l_orientation_coefficient*l_main_controller.Axis1.get_percent()));
    m_back_right_motor.set_desired_velocity(l_translation_coefficient*l_main_controller.Axis3.get_percent()+l_translation_coefficient*l_main_controller.Axis4.get_percent()-(l_orientation_coefficient*l_main_controller.Axis1.get_percent()));
}

int Holonomic::task(){
  if(m_robot.get_robot_state() == ROBOT_DRIVER_CONTROL){
    driver_control();
  }
  else if(m_robot.get_robot_state() == ROBOT_AUTONOMOUS){
    autonomous();
  }
  return 0;
}
