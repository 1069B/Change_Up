#include "robot/robot_class.hpp"
#include "robot/subsystems/autonomous_class.hpp"

void Robot::define_autonomous_routines(){

	/* Skills */
	Autonomous_Routine l_skills = add_autonomous_routine("Skills", ROBOT_SKILLS);
	Autonomous_Routine::set_selected_routine("Skills");

	/* Lower Right Goal */
	l_skills.add_robot_event(Base_Event::base_move(50,0,48, 2800), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(25,0, 0, 600), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_stationary(1000), Intake_Event::intake_store(), Lift_Event::lift_score());// Wait for score, Store Intakes, Score One Ball

	/* Middle Right Goal */
	l_skills.add_robot_event(Base_Event::base_move(100, 180, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(0, 0, 50, 870), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(100, 90, 0, 3000), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_stationary(1000), Intake_Event::intake_store(), Lift_Event::lift_score());// Wait for score, Store Intakes, Score One Ball

	/* Top Right Goal */
	l_skills.add_robot_event(Base_Event::base_move(100, 180, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(0, 0, 50, 870), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(100, 90, 0, 3000), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(0, 0, -50, 1000), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_stationary(1000), Intake_Event::intake_store(), Lift_Event::lift_score());// Wait for score, Store Intakes, Score One Ball
}
// /* Lower Right Goal */
	// m_autonomous.manipulator_feild(MANIPULATOR_INTAKE_SENSOR);// Pick Up Ball in front of robot
	// m_autonomous.delay(1700);// Delay for Arms to grab the ball
	// m_autonomous.manipulator_feild(MANIPULATOR_INTAKE_STORE);// Transistion into score a ball
	// m_autonomous.move_base(0, 50, 0, 48, 2800);// Turn Base towards goal
	// m_autonomous.move_base(0, 25, 0, 0, 600);// Move Base forward towards goal
	// m_autonomous.manipulator_score(MANIPULATOR_INTAKE_STORE);
	// m_autonomous.delay(2000);//Wait for the robot to score the center

	// /* Middle Right Goal */
	// m_autonomous.move_base(0, 100, 180, 0, 700);// Back away from the lower right goal
	// m_autonomous.move_base(0, 0, 0, 50, 870);// Rotate towards the center right ball
	// m_autonomous.manipulator_feild(MANIPULATOR_INTAKE_STORE);
	// m_autonomous.move_base(0, 100, 90, 0, 3000);// Move towards the center right ball
	// m_autonomous.manipulator_score(MANIPULATOR_INTAKE_STORE);
	// m_autonomous.delay(2000);//Wait for the robot to score the center

	// /* Center Goal */
	// m_autonomous.move_base(0, 75, 180, 0, 300);// Move back from Middle Right Goal
	// m_autonomous.manipulator_feild(MANIPULATOR_INTAKE_SENSOR);// Pick Up Ball in front of robot
	// m_autonomous.move_base(0, 0, 0, 50, 3500);// Turn to face center goal
	// m_autonomous.move_base(0, 75, 0, 0, 1000);// Move Towards Center Goal
	// m_autonomous.move_base(0, 0, 0, 50, 1000);
	// m_autonomous.move_base(0, 100, 270, 0, 1500);
	// m_autonomous.manipulator_feild(MANIPULATOR_INTAKE_DEPLOY);
	// m_autonomous.move_base(0, 75, 0, 0, 1000);
	// m_autonomous.manipulator_score(MANIPULATOR_INTAKE_DEPLOY);// Score one red and remove all of the blue
	//m_autonomous.delay(3000);//Wait for the robot to score the center

	// /* Upper Left Goal */
	// m_autonomous.move_base(0, 75, 180, 0, 1000);// Back away from the center goal
	// m_autonomous.manipulator_feild();// Pick Up Ball in front of robot
	// m_autonomous.move_base(0, 0, 0, -36, 1000);// Turn Towards Ball above Center Goal
	// m_autonomous.move_base(0, 75, 0, 0, 4500);// Move towards Ball above Center goal
	// m_autonomous.manipulator_score_goal();// Transistion into score a ball
	// m_autonomous.move_base(0, 75, 5, 0, 3700);// Move towards Upper Left Goal
	// m_autonomous.delay(1000);//Wait for the robot to score

	// /* Middle Left Goal */
	// m_autonomous.move_base(0, 40, 180, 0, 1000);// Back Away from Upper Left Goal
	// m_autonomous.move_base(0, 0, 0, 50, 2500);// Turn towards ball between Upper and Middle Left Goals
	// m_autonomous.manipulator_feild();// Pick Up Ball in front of robot
	// m_autonomous.move_base(0, 75, 0, 0, 2000);// Move twards ball
	// m_autonomous.manipulator_score_goal();// Transistion into score a ball 
	// m_autonomous.move_base(0, 75, 0, 0, 2000);// Move towards Middle Left Goal
	// m_autonomous.move_base(0, 0, 0, -40, 2000);// Turn towards Middle Left Goal
	// m_autonomous.move_base(0, 40, 0, 0, 500);// Move Towards Middle Left Goal
	// m_autonomous.delay(1000);//Wait for the robot to score

	// /* Bottom Left Goal */
	// m_autonomous.move_base(0, 40, 180, 0, 500);// Move Away from Middle Left Goal
	// m_autonomous.move_base(0, 0, 0, 50, 3000);// Turn towards ball between Middle and Lower Left Goals
	// m_autonomous.manipulator_feild();// Pick Up Ball in front of robot
	// m_autonomous.move_base(0, 75, 0, 0, 2000);// Move towards ball
	// m_autonomous.manipulator_score_goal();// Transistion into score a ball 
	// m_autonomous.move_base(0, 0, 0, -40, 2000);// Turn Towards the Goal
	// m_autonomous.move_base(0, 40, 0, 0, 500);// Move Towards Bottom Left Goal
	// m_autonomous.delay(1000);//Wait for the robot to score

	// /* Bottom Center Goal */
	// m_autonomous.move_base(0, 40, 180, 0, 500);// Move Away from the Bottom Center Goal
	// m_autonomous.manipulator_feild();// Pick Up Ball in front of robot
	// m_autonomous.move_base(0, 0, 0, 50, 3000);// Turn towards the ball above the bottom Center Goal
	// m_autonomous.move_base(0, 75, 180, 0, 5000);// Move towards the ball
	// m_autonomous.move_base(0, 0, 0, -40, 3000);// Turn towards the Bottom Center Goal
	// m_autonomous.manipulator_score_goal();// Transistion into score a ball 
	// m_autonomous.move_base(0, 75, 0, 0, 2000);// Move towards the Bottom Center Goal
	// m_autonomous.delay(1000);//Wait for the robot to score

	// /* Ending */
	// m_autonomous.move_base(0, 75, 180, 0, 2000);// Move away from goal