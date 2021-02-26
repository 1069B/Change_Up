#include "robot/robot_class.hpp"
#include "robot/subsystems/autonomous_class.hpp"
#include "robot/subsystems/autonomous_rountines_class.hpp"

#define FULL_TURN 90
#define FULL_TRANSLATION 100
#define SCORE_TIME 350

/* Red Autonomous Routines */
void define_red_home_row(Robot& p_robot){
	Autonomous_Routine& l_home_row = p_robot.get_autonomous().add_autonomous_routine("Red_Home_Row", ROBOT_RED);
}

void define_red_left_two_goals(Robot& p_robot){
	Autonomous_Routine& l_two_goals = p_robot.get_autonomous().add_autonomous_routine("Red_Two_Goals", ROBOT_RED);
}

void define_red_left_corner(Robot& p_robot){
	Autonomous_Routine& l_left_corner = p_robot.get_autonomous().add_autonomous_routine("Red_Left_Corner", ROBOT_RED);
}

void define_red_right_corner(Robot& p_robot){
	Autonomous_Routine& l_right_corner = p_robot.get_autonomous().add_autonomous_routine("Red_Right_Corner", ROBOT_RED);
}

/* Blue Autonomous Routines */
void define_blue_home_row(Robot& p_robot){
	Autonomous_Routine& l_home_row = p_robot.get_autonomous().add_autonomous_routine("Blue_Home_Row", ROBOT_BLUE);
}

void define_blue_left_two_goals(Robot& p_robot){
	Autonomous_Routine& l_two_goals = p_robot.get_autonomous().add_autonomous_routine("Blue_Two_Goals", ROBOT_BLUE);
}

void define_blue_left_corner(Robot& p_robot){
	Autonomous_Routine& l_left_corner = p_robot.get_autonomous().add_autonomous_routine("Blue_Left_Corner", ROBOT_BLUE);
}

void define_blue_right_corner(Robot& p_robot){
	Autonomous_Routine& l_right_corner = p_robot.get_autonomous().add_autonomous_routine("Blue_Right_Corner", ROBOT_BLUE);
}

/* Skills Routines */
void define_skills(Robot& p_robot){
	Autonomous_Routine& l_skills = p_robot.get_autonomous().add_autonomous_routine("Skills", ROBOT_SKILLS);
	p_robot.set_robot_alliance(ROBOT_SKILLS);
	p_robot.get_autonomous().set_selected_routine(l_skills);

	/* Lower Right Goal */
	l_skills.add_robot_event(Base_Event::base_stationary(750), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(94.5, 0, 75, 2320), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_stationary(SCORE_TIME), Intake_Event::intake_store(), Lift_Event::lift_score());// Wait for score, Store Intakes, Score One Ball

	/* Middle Right Goal */
	l_skills.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 1200), Intake_Event::intake_store(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(0, 0, FULL_TURN, 960), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(150, 90, 0, 2550), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 0, 0, 600), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_stationary(SCORE_TIME), Intake_Event::intake_store(), Lift_Event::lift_score());// Wait for score, Store Intakes, Score One Ball

	/* Top Right Goal */
	l_skills.add_robot_event(Base_Event::base_move(100, 180, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(0, 0, FULL_TURN, 1150), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 85, 0, 1600), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(75, 2, 0, 4800), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_stationary(SCORE_TIME), Intake_Event::intake_store(), Lift_Event::lift_score());// Wait for score, Store Intakes, Score One Ball

	/* Top Middle Goal */
	l_skills.add_robot_event(Base_Event::base_move(100, 180, 0, 2850), Intake_Event::intake_goal(1000), Lift_Event::lift_score());
	l_skills.add_robot_event(Base_Event::base_move(0, 0, FULL_TURN, 1850), Intake_Event::intake_stationary(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 0, 0, 3000), Intake_Event::intake_grab(INTAKE_RETRACT_OPEN), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(0, 0, -FULL_TURN, 1550), Intake_Event::intake_grab(INTAKE_RETRACT_OPEN), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(125, 0, 0, 2200), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_stationary(SCORE_TIME), Intake_Event::intake_store(), Lift_Event::lift_score());// Wait for score, Store Intakes, Score One Ball

	/* Top Left Goal */
	l_skills.add_robot_event(Base_Event::base_move(100, 180, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(0, 0, FULL_TURN, 1500), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(125, 353, 0, 3100), Intake_Event::intake_grab(INTAKE_RETRACT_OPEN), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(0, 0, -FULL_TURN, 1000), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(100, 0, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_stationary(SCORE_TIME), Intake_Event::intake_store(), Lift_Event::lift_score());// Wait for score, Store Intakes, Score One Ball

	/* Left Middle Goal */
	l_skills.add_robot_event(Base_Event::base_move(50, 180, 100, 1770), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 0, 0, 4400), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(0, 0, -FULL_TURN, 1300), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 0, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_stationary(SCORE_TIME), Intake_Event::intake_store(), Lift_Event::lift_score());// Wait for score, Store Intakes, Score One Ball

	/* Center Goal */
	l_skills.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(0, 0, -FULL_TURN, 2500), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 352, 0, 3000), Intake_Event::intake_goal(500), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(0, 0, FULL_TURN, 500), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_stationary(SCORE_TIME), Intake_Event::intake_goal(), Lift_Event::lift_score());// Wait for score, Store Intakes, Score One Ball

	/* Lower Left Goal */
	l_skills.add_robot_event(Base_Event::base_move(150, 180, 0, 1000), Intake_Event::intake_goal(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(0, 0, 125, 1000), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(150, 0, 0, 2000), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_stationary(SCORE_TIME), Intake_Event::intake_store(), Lift_Event::lift_score());// Wait for score, Store Intakes, Score One Ball
}

void Robot::define_autonomous_routines(){
	/* Red Autonomous Routines */
	define_red_home_row(*this);
	define_red_left_two_goals(*this);
	define_red_left_corner(*this);
	define_red_right_corner(*this);

	/* Blue Autonomous Routines */
	define_blue_home_row(*this);
	define_blue_left_two_goals(*this);
	define_blue_left_corner(*this);
	define_blue_right_corner(*this);

	/* Skills Autonomous Routines */
	define_skills(*this);

	
}