#include "robot/robot_class.hpp"
#include "robot/subsystems/manipulator.hpp"


Robot g_robot{};

void initialize(){
	g_robot.set_robot_state(ROBOT_INITIALIZATION);
	g_robot.initialize();
}

void disabled(){
	g_robot.set_robot_state(ROBOT_DISABLED);
}

void competition_initialize() {
	g_robot.initialize();
	g_robot.set_robot_state(ROBOT_INITIALIZATION);
}

void autonomous(){
	g_robot.set_robot_state(ROBOT_AUTONOMOUS);
	g_robot.task();
}

void opcontrol(){
	g_robot.set_robot_state(ROBOT_DRIVER_CONTROL);

	while(true){
		g_robot.task();
		pros::delay(20);
	}
}