#include "robot/subsystems/base_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/devices/controller_class.hpp"
#include "robot/robot_class.hpp"

Base::Base(Robot &p_robot):
m_robot(p_robot),
m_front_left_motor(m_robot.find_motor("Front Left Base")),
m_front_right_motor(m_robot.find_motor("Front Right Base")),
m_back_left_motor(m_robot.find_motor("Back Left Base")),
m_back_right_motor(m_robot.find_motor("Back Right Base"))
{

}

double Base::speedUp(int p_controllerValue){
  double l_a = 201;
	double l_b = 5;
	double l_c = 0.05;
	double l_h = -27;
  if(p_controllerValue != 0){
    if(p_controllerValue > 5){
      return l_a/(1+(l_a - l_b)/l_b * pow(M_E, (-l_c*(p_controllerValue + l_h))));
    }
    else if(p_controllerValue < -5){
      return -l_a/(1+(l_a - l_b)/l_b * pow(M_E, (l_c*(p_controllerValue - l_h))));
    }
    else
      return 0;
  }
  return 0;
}

int Base::task(){
  CONTROLLER::Controller main_controller(pros::E_CONTROLLER_MASTER);
	CONTROLLER::Controller partner_controller(pros::E_CONTROLLER_PARTNER);


  return 0;
}
