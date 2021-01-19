#include "main.h"
#include "robot/robot_class.hpp"
#include "robot/devices/motor_class.hpp"
#include "robot/devices/controller_class.hpp"

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
	g_robot.add_motor("Front Left Base", 1, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false);
	g_robot.add_motor("Front Right Base", 2, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false);
	g_robot.add_motor("Back Left Base", 3, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false);
	g_robot.add_motor("Back RIght Base", 4, pros::E_MOTOR_GEARSET_18, pros::E_MOTOR_BRAKE_COAST, false);

	g_robot.add_motor("Left Intake", 11, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_HOLD, false);
	g_robot.add_motor("Right Intake", 20, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_HOLD, true);

	g_robot.add_motor("Intial Rollers", 9, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_COAST, true);
	g_robot.add_motor("Second Rollers", 10, pros::E_MOTOR_GEARSET_06, pros::E_MOTOR_BRAKE_COAST, true);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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
void autonomous() {}

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
void opcontrol(){
	CONTROLLER::Controller main_controller(pros::E_CONTROLLER_MASTER);
	CONTROLLER::Controller partner_controller(pros::E_CONTROLLER_PARTNER);

	Motor& front_left_base = g_robot.find_motor("Front Left Base");
	Motor& front_right_base = g_robot.find_motor("Front Right Base");
	Motor& back_left_base = g_robot.find_motor("Back Left Base");
	Motor& back_right_base = g_robot.find_motor("Back RIght Base");

	Motor& left_intake = g_robot.find_motor("Left Intake");
	Motor& right_intake = g_robot.find_motor("Right Intake");

	Motor& intial_roller = g_robot.find_motor("Intial Rollers");
	Motor& second_roller = g_robot.find_motor("Second Rollers");

	int speed{};
	Intake_State intake_current_state{USER};
	Intake_State intake_previous_state{USER};

	Intake_State roller_current_state{USER};
	Intake_State roller_previous_state{USER};

	while (true) {
		g_robot.task();
		if(partner_controller.Axis3.get_percent() != 0){
			intake_current_state = USER;
		}
		else if(partner_controller.ButtonL1.get_state()){
			intake_current_state = FORWARD;
		}
		else if(partner_controller.ButtonL2.get_state()){
			intake_current_state = BACK_PRESET;
		}


		if(intake_current_state == USER){
			left_intake.set_desired_velocity(partner_controller.Axis3.get_percent() * 600);
			right_intake.set_desired_velocity(partner_controller.Axis3.get_percent() * 600);
		}
		else if(intake_previous_state != intake_current_state){
			if(intake_current_state ==  FORWARD){
				left_intake.set_desired_velocity(600);
				right_intake.set_desired_velocity(600);
			}
			else if(intake_current_state ==  BACK_PRESET && intake_previous_state != BACK_PRESET){
				left_intake.set_desired_velocity(-200);
				right_intake.set_desired_velocity(-200);
			}
		}
		intake_previous_state = intake_current_state;


		if(partner_controller.Axis2.get_percent() != 0){
			roller_current_state = USER;
		}
		else if(partner_controller.ButtonR1.get_state()){
			roller_current_state = FORWARD;
		}
		else if(partner_controller.ButtonR2.get_state()){
			roller_current_state = BACK_PRESET;
		}


		if(roller_current_state == USER){
			intial_roller.set_desired_velocity(partner_controller.Axis2.get_percent() * 600.0);
			second_roller.set_desired_velocity(partner_controller.Axis2.get_percent() * 600.0);
		}
		else if(roller_previous_state != roller_current_state){
			if(roller_current_state ==  FORWARD){
				intial_roller.set_desired_velocity(600);
				second_roller.set_desired_velocity(600);
			}
			else if(roller_current_state ==  BACK_PRESET){
				intial_roller.set_desired_velocity(600);
				second_roller.set_desired_velocity(-600);
			}
		}
		roller_previous_state = roller_current_state;

		pros::delay(20);
	}
}
