#include "main.h"
#include "robot/robot_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/devices/controller_class.hpp"
#include "robot/subsystems/autonomous_class.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

Robot g_robot{};

enum Intake_State{
	FORWARD,
	BACK_PRESET,
	USER
};

void initialize(){
	g_robot.defineGUI();
	g_robot.add_motor("Front Left Base", 15, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false);
	g_robot.add_motor("Front Right Base", 16, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, true);
	g_robot.add_motor("Back Left Base", 5, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false);
	g_robot.add_motor("Back Right Base", 6, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, true);

	g_robot.add_motor("Left Intake", 12, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_COAST, false);
	g_robot.add_motor("Right Intake", 19, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_COAST, true);

	g_robot.add_motor("Intial Rollers", 9, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_BRAKE, true);
	g_robot.add_motor("Second Rollers", 10, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_COAST, true);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled(){
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous(){
	Autonomous l_auton(g_robot);
	l_auton.start_auton();
	l_auton.move_balls(0, 600, 600, 0, 1500);
	l_auton.turn_intakes_on(-400);
	l_auton.move_base(1000, 50, 0, 48, 2800);
	l_auton.turn_intakes_off();
	l_auton.move_base(1000, 25, 0, 0, 600);
	l_auton.move_balls(3000, 0, 0, 600, 1000);
	l_auton.move_base(5000, 75, 180, -9, 4900);
	l_auton.move_base(7000, 0, 0, -41, 2200);

	l_auton.move_balls(10000, 0, 600, 0, 1000);
	l_auton.move_base(10000, 75, 0, 0, 1700);
	l_auton.move_balls(10000, 600, 0, 600, 1200);
	l_auton.move_balls(10000, 600, 600, -600, 1700);
	l_auton.turn_intakes_on(-50);
	l_auton.move_base(10000, 75, 180, 0, 1000);
	l_auton.move_balls(10000, 600, 600, -600, 3500);
	l_auton.turn_intakes_on(-400);

	l_auton.move_base(22000, 0, 0, -36, 1000);
	l_auton.move_base(25000, 75, 0, 0, 3000);
	l_auton.turn_intakes_on(600);
	l_auton.turn_intial_roller_on(600);
	l_auton.move_base(25000, 75, 0, 0, 1500);
	l_auton.turn_intakes_on(-400);
	l_auton.move_base(25000, 75, 5, 0, 3700);
	l_auton.turn_intakes_off();
	l_auton.turn_intial_roller_off();
	l_auton.move_balls(3000, 0, 600, 600, 2000);

	l_auton.move_base(30000, 40, 180, 0, 1000);
	l_auton.move_base(30000, 0, 0, 50, 2500);
	l_auton.turn_intakes_on(600);
	l_auton.turn_intial_roller_on(600);
	l_auton.move_base(32000, 75, 0, 0, 2000);
	l_auton.turn_intakes_on(-400);
	l_auton.turn_intial_roller_off();
	l_auton.move_base(32000, 75, 0, 0, 2000);
	l_auton.turn_intial_roller_off();

	l_auton.move_base(35000, 0, 0, -40, 2000);
	l_auton.move_base(35000, 40, 0, 0, 500);
	l_auton.move_balls(35000, 0, 600, 600, 3000);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 double speedUp(int p_controllerValue){
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

void opcontrol(){
	CONTROLLER::Controller main_controller(pros::E_CONTROLLER_MASTER);
	CONTROLLER::Controller partner_controller(pros::E_CONTROLLER_PARTNER);

	Motor& m_front_left_motor = g_robot.find_motor("Front Left Base");
	Motor& m_front_right_motor = g_robot.find_motor("Front Right Base");
	Motor& m_back_left_motor = g_robot.find_motor("Back Left Base");
	Motor& m_back_right_motor = g_robot.find_motor("Back Right Base");

	Motor& left_intake = g_robot.find_motor("Left Intake");
	Motor& right_intake = g_robot.find_motor("Right Intake");

	Motor& intial_roller = g_robot.find_motor("Intial Rollers");
	Motor& second_roller = g_robot.find_motor("Second Rollers");


	while (true) {
		g_robot.task();
		if(partner_controller.ButtonL1.get_state()){
			left_intake.set_desired_velocity(600);
			right_intake.set_desired_velocity(600);
		}
		else if(partner_controller.ButtonL2.get_state()){
			left_intake.set_desired_velocity(-200);
			right_intake.set_desired_velocity(-200);
		}
		else{
			left_intake.set_desired_velocity(partner_controller.Axis3.get_percent() * 600);
			right_intake.set_desired_velocity(partner_controller.Axis3.get_percent() * 600);
			intial_roller.set_desired_velocity(fabs(partner_controller.Axis3.get_percent() * 600.0));
		}


		if(partner_controller.ButtonR1.get_state()){
			intial_roller.set_desired_velocity(600);
			second_roller.set_desired_velocity(600);
		}
		else if(partner_controller.ButtonR2.get_state()){
			intial_roller.set_desired_velocity(600);
			second_roller.set_desired_velocity(-600);
		}
		else{
			second_roller.set_desired_velocity(partner_controller.Axis2.get_percent() * 600.0);
		}

	  m_front_left_motor.set_desired_velocity((int)speedUp(200*main_controller.Axis3.get_percent()+200*main_controller.Axis4.get_percent()+(200*main_controller.Axis1.get_percent()/1.1)));
	  m_front_right_motor.set_desired_velocity((int)speedUp(200*main_controller.Axis3.get_percent()-200*main_controller.Axis4.get_percent()-(200*main_controller.Axis1.get_percent()/1.1)));
	  m_back_left_motor.set_desired_velocity((int)speedUp(200*main_controller.Axis3.get_percent()-200*main_controller.Axis4.get_percent()+(200*main_controller.Axis1.get_percent()/1.1)));
	  m_back_right_motor.set_desired_velocity((int)speedUp(200*main_controller.Axis3.get_percent()+200*main_controller.Axis4.get_percent()-(200*main_controller.Axis1.get_percent()/1.1)));
		pros::delay(20);
	}
}
