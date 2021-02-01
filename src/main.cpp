#include "robot/robot_class.hpp"


Robot g_robot{};

void initialize(){
	g_robot.set_robot_state(ROBOT_INITIALIZATION);
	g_robot.defineGUI();
}



void disabled(){
	g_robot.set_robot_state(ROBOT_DISABLED);
}



void competition_initialize() {
	g_robot.set_robot_state(ROBOT_INITIALIZATION);
}



void autonomous(){
	g_robot.set_robot_state(ROBOT_AUTONOMOUS);
}



void opcontrol(){
	g_robot.set_robot_state(ROBOT_DRIVER_CONTROL);

	while(true){
		g_robot.task();
		pros::delay(20);
	}
}