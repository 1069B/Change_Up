#include "robot/robot_class.hpp"


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

	// Autonomous l_auton(g_robot);
	// l_auton.start_auton();
	// l_auton.move_balls(0, 600, 600, 0, 1500);
	// l_auton.turn_intakes_on(-400);
	// l_auton.move_base(1000, 50, 0, 48, 2800);
	// l_auton.turn_intakes_off();
	// l_auton.move_base(1000, 25, 0, 0, 600);
	// l_auton.move_balls(3000, 0, 0, 600, 1000);
	// l_auton.move_base(5000, 75, 180, -9, 4900);
	// l_auton.move_base(7000, 0, 0, -41, 2200);

	// l_auton.move_balls(10000, 0, 600, 0, 1000);
	// l_auton.move_base(10000, 75, 0, 0, 1700);
	// l_auton.move_balls(10000, 600, 0, 600, 1200);
	// l_auton.move_balls(10000, 600, 600, -600, 1700);
	// l_auton.turn_intakes_on(-50);
	// l_auton.move_base(10000, 75, 180, 0, 1000);
	// l_auton.move_balls(10000, 600, 600, -600, 3500);
	// l_auton.turn_intakes_on(-400);

	// l_auton.move_base(22000, 0, 0, -36, 1000);
	// l_auton.move_base(25000, 75, 0, 0, 3000);
	// l_auton.turn_intakes_on(600);
	// l_auton.turn_intial_roller_on(600);
	// l_auton.move_base(25000, 75, 0, 0, 1500);
	// l_auton.turn_intakes_on(-400);
	// l_auton.move_base(25000, 75, 5, 0, 3700);
	// l_auton.turn_intakes_off();
	// l_auton.turn_intial_roller_off();
	// l_auton.move_balls(3000, 0, 600, 600, 2000);

	// l_auton.move_base(30000, 40, 180, 0, 1000);
	// l_auton.move_base(30000, 0, 0, 50, 2500);
	// l_auton.turn_intakes_on(600);
	// l_auton.turn_intial_roller_on(600);
	// l_auton.move_base(32000, 75, 0, 0, 2000);
	// l_auton.turn_intakes_on(-400);
	// l_auton.turn_intial_roller_off();
	// l_auton.move_base(32000, 75, 0, 0, 2000);
	// l_auton.turn_intial_roller_off();

	// l_auton.move_base(35000, 0, 0, -40, 2000);
	// l_auton.move_base(35000, 40, 0, 0, 500);
	// l_auton.move_balls(35000, 0, 600, 600, 3000);
}

void opcontrol(){
	g_robot.set_robot_state(ROBOT_DRIVER_CONTROL);

	while(true){
		g_robot.task();
		pros::delay(20);
	}
}