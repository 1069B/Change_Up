#include "robot/subsystems/holonomic_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/devices/controller_class.hpp"
#include "robot/robot_class.hpp"

Holonomic::Holonomic(Robot &p_robot):
m_robot(p_robot),
m_front_left_motor(m_robot.add_motor("Front Left Base", 15, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false)),
m_front_right_motor(m_robot.add_motor("Front Right Base", 16, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, true)),
m_back_left_motor(m_robot.add_motor("Back Left Base", 5, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false)),
m_back_right_motor(m_robot.add_motor("Back Right Base", 6, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, true))
{
}

void Holonomic::autonomous(){
  /*
Functions /  States 

1 - Translation: Defined X, Defined Y, Constant Ori
2 - ORIENTATION: Constant X, Constatnt Y, Defined Ori
3 - Turn: Defined X, Defined Y, Defined Ori

4 - Pose

5 - Align to Goal

*/
//PID: X

  //PID: Y

  //PID Ori

  // PIDS calculate the different speeds

      

  int l_x_vel;
  int l_y_vel;
  int l_ori_vel;

  m_desired_trajectory.m_orientation_velocity;
  m_desired_trajectory.m_translation_velocity = sqrtf(powf(l_x_vel,2) + powf(l_y_vel,2));
  m_desired_trajectory.m_translation_angle = atanf(l_y_vel/l_x_vel);

  m_desired_velocities.m_front_left = (sin(m_desired_trajectory.m_translation_angle+(M_PI/4.0)) * m_desired_trajectory.m_translation_velocity) - m_desired_trajectory.m_orientation_velocity;
  m_desired_velocities.m_front_right = (-cos(m_desired_trajectory.m_translation_angle+(M_PI/4.0)) * m_desired_trajectory.m_translation_velocity) + m_desired_trajectory.m_orientation_velocity;
  m_desired_velocities.m_back_left = (-cos(m_desired_trajectory.m_translation_angle+(M_PI/4.0)) * m_desired_trajectory.m_translation_velocity) - m_desired_trajectory.m_orientation_velocity;
  m_desired_velocities.m_back_right = (sin(m_desired_trajectory.m_translation_angle+(M_PI/4.0)) * m_desired_trajectory.m_translation_velocity) + m_desired_trajectory.m_orientation_velocity;
}

double Holonomic::speed_up(int p_controllerValue){
  if(abs(p_controllerValue) < 170){
    return p_controllerValue/2.0;
  }
  return p_controllerValue;


  // double l_a = m_acceleration_coefficients.m_coefficient_A;
	// double l_b = m_acceleration_coefficients.m_coefficient_B;
	// double l_c = m_acceleration_coefficients.m_coefficient_C;
	// double l_h = m_acceleration_coefficients.m_coefficient_H;
  // if(p_controllerValue != 0){
  //   if(p_controllerValue > 5)
  //     return l_a/(1+(l_a - l_b)/l_b * pow(M_E, (-l_c*(p_controllerValue + l_h))));
  //   else if(p_controllerValue < -5)
  //     return -l_a/(1+(l_a - l_b)/l_b * pow(M_E, (l_c*(p_controllerValue - l_h))));
  // }
  // return 0;
}

void Holonomic::base_set_vector(double p_translational_velocity, double p_orientation, double p_turning_velocity){
  m_front_left_motor.set_desired_velocity(cos((p_orientation/180.0*M_PI) + (M_PI/4.0)) * p_translational_velocity - p_turning_velocity);
  m_front_right_motor.set_desired_velocity(sin((p_orientation/180.0*M_PI) + (M_PI/4.0)) * p_translational_velocity + p_turning_velocity);
  m_back_left_motor.set_desired_velocity(sin((p_orientation/180.0*M_PI) + (M_PI/4.0)) * p_translational_velocity - p_turning_velocity);
  m_back_right_motor.set_desired_velocity(cos((p_orientation/180.0*M_PI) + (M_PI/4.0)) * p_translational_velocity + p_turning_velocity);
}

int Holonomic::task(){
  CONTROLLER::Controller& l_main_controller = m_robot.get_main_controller();
	CONTROLLER::Controller& l_partner_controller = m_robot.get_partner_controller();
  
  if(m_robot.get_robot_state() == ROBOT_DRIVER_CONTROL){
    m_front_left_motor.set_desired_velocity((int)speed_up(200*l_main_controller.Axis3.get_percent()+200*l_main_controller.Axis4.get_percent()+(200*l_main_controller.Axis1.get_percent()/1.25)));
	  m_front_right_motor.set_desired_velocity((int)speed_up(200*l_main_controller.Axis3.get_percent()-200*l_main_controller.Axis4.get_percent()-(200*l_main_controller.Axis1.get_percent()/1.25)));
	  m_back_left_motor.set_desired_velocity((int)speed_up(200*l_main_controller.Axis3.get_percent()-200*l_main_controller.Axis4.get_percent()+(200*l_main_controller.Axis1.get_percent()/1.25)));
	  m_back_right_motor.set_desired_velocity((int)speed_up(200*l_main_controller.Axis3.get_percent()+200*l_main_controller.Axis4.get_percent()-(200*l_main_controller.Axis1.get_percent()/1.25)));
  }
  else if(m_robot.get_robot_state() == ROBOT_AUTONOMOUS){

  }
  else if(m_robot.get_robot_state() == ROBOT_INITIALIZATION){

  }
  else{

  }
  return 0;
}
