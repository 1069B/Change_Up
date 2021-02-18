#include "robot/robot_class.hpp"
#include "robot/subsystems/manipulator.hpp"


Robot g_robot{};

void initialize(){
	g_robot.set_robot_state(ROBOT_INITIALIZATION);
	g_robot.initialize();

	while(true){
		g_robot.task();
		pros::delay(10);
	}
}

void disabled(){
	g_robot.set_robot_state(ROBOT_DISABLED);
}

void competition_initialize() {
	g_robot.initialize();
	g_robot.set_robot_state(ROBOT_INITIALIZATION);

	while(true){
		g_robot.task();
		pros::delay(10);
	}
}

void autonomous(){
	g_robot.set_robot_state(ROBOT_AUTONOMOUS);
	
	while(true){
		g_robot.task();
		pros::delay(10);
	}
}

void opcontrol(){
	g_robot.set_robot_state(ROBOT_DRIVER_CONTROL);

	while(true){
		g_robot.task();
		pros::delay(10);
	}
}