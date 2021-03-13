#include "robot/robot_class.hpp"

#include "robot/subsystems/manipulator.hpp"
#include "robot/subsystems/autonomous_class.hpp"
#include "robot/graphical_interface/screen_class.hpp"
#include "robot/subsystems/odometry_class.hpp"

Robot g_robot{};

void initialize(){
	g_robot.set_robot_state(ROBOT_INITIALIZATION);
	g_robot.initialize();
	g_robot.defineGUI();

	g_robot.set_robot_state(ROBOT_DISABLED);
	while(g_robot.get_robot_state() == ROBOT_DISABLED){
		g_robot.task();
		pros::delay(10);
	}
}

void disabled(){
	g_robot.set_robot_state(ROBOT_DISABLED);
	while(g_robot.get_robot_state() == ROBOT_DISABLED){
		g_robot.task();
		pros::delay(10);
	}
}

void competition_initialize(){
	initialize();
}

void autonomous(){
	g_robot.initialize();
	g_robot.set_robot_state(ROBOT_AUTONOMOUS);

	g_robot.get_autonomous().start_autonomous();
	while(g_robot.get_autonomous().is_running()){
		g_robot.task();
		pros::delay(20);
	}

	g_robot.get_autonomous().end_autonomous();
	
	while(g_robot.get_robot_state() == ROBOT_AUTONOMOUS){
		GUI::Screen::task();
		g_robot.get_odometry().task();
		pros::delay(20);
	}
}

void opcontrol(){
	g_robot.initialize();
	g_robot.set_robot_state(ROBOT_DRIVER_CONTROL);
	
	while(g_robot.get_robot_state() == ROBOT_DRIVER_CONTROL){
		g_robot.task();
		pros::delay(10);
	}
}