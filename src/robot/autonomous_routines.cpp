#include "robot/robot_class.hpp"
#include "robot/subsystems/autonomous_class.hpp"
#include "robot/subsystems/autonomous_rountines_class.hpp"

#define FULL_TURN 90
#define FULL_TRANSLATION 100
#define SCORE_TIME 350

/* Red Autonomous Routines */
void define_red_corner_and_center(Robot& p_robot){
	Autonomous_Routine& red_corner_and_center = p_robot.get_autonomous().add_autonomous_routine("Red_Corner_and_Center", ROBOT_RED);

	/* Red Corner Goal */
	red_corner_and_center.add_robot_event(Base_Event::base_move(100, 270, 40, 1800), Intake_Event::intake_stationary(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	red_corner_and_center.add_robot_event(Base_Event::base_move(120, 0, 0, 1400), Intake_Event::intake_store(), Lift_Event::lift_sort());
	red_corner_and_center.add_robot_event(Base_Event::base_stationary(400), Intake_Event::intake_store(), Lift_Event::lift_score_one());// Wait for score, Store Intakes, Score One Ball

	/* Center Goal Ball */
	red_corner_and_center.add_robot_event(Base_Event::base_move(150, 180, 0, 1600), Intake_Event::intake_goal(), Lift_Event::lift_sort());
	red_corner_and_center.add_robot_event(Base_Event::base_move(0, 0, -FULL_TURN, 2000), Intake_Event::intake_grab(INTAKE_RETRACT_OPEN), Lift_Event::lift_sort());
	red_corner_and_center.add_robot_event(Base_Event::base_align_to_goal(150, 0, 0, 1600), Intake_Event::intake_grab(INTAKE_RETRACT_NONE), Lift_Event::lift_sort());

	/* Center Goal */
	red_corner_and_center.add_robot_event(Base_Event::base_move(150, 280, 0, 1700), Intake_Event::intake_stationary(), Lift_Event::lift_sort());
	red_corner_and_center.add_robot_event(Base_Event::base_move(100, 180, 0, 950), Intake_Event::intake_stationary(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());
	red_corner_and_center.add_robot_event(Base_Event::base_move(100, 300, 19, 1900), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());
	red_corner_and_center.add_robot_event(Base_Event::base_stationary(3000), Intake_Event::intake_stationary(), Lift_Event::lift_score_all());
}

void define_red_left_two_goals(Robot& p_robot){
	Autonomous_Routine& l_left_two_goals = p_robot.get_autonomous().add_autonomous_routine("Red_Left_Two_Goals", ROBOT_RED);

	/* Red Corner Goal */
	l_left_two_goals.add_robot_event(Base_Event::base_move(100, 270, 40, 1800), Intake_Event::intake_stationary(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_left_two_goals.add_robot_event(Base_Event::base_move(120, 0, 0, 1400), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_left_two_goals.add_robot_event(Base_Event::base_stationary(400), Intake_Event::intake_store(), Lift_Event::lift_score_one());// Wait for score, Store Intakes, Score One Ball

	/* Red Middle Goal */
	l_left_two_goals.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 1200), Intake_Event::intake_store(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_left_two_goals.add_robot_event(Base_Event::base_move(0, 0, FULL_TURN, 960), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_left_two_goals.add_robot_event(Base_Event::base_move(150, 90, 0, 2600), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_left_two_goals.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 0, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_left_two_goals.add_robot_event(Base_Event::base_stationary(SCORE_TIME), Intake_Event::intake_store(), Lift_Event::lift_score_one());

	l_left_two_goals.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 1000), Intake_Event::intake_stationary(), Lift_Event::lift_stationary());
}

void define_red_right_two_goals(Robot& p_robot){
	Autonomous_Routine& l_right_two_goals = p_robot.get_autonomous().add_autonomous_routine("Red_Right_Two_Goals", ROBOT_RED);

	/* Red Corner Goal */
	l_right_two_goals.add_robot_event(Base_Event::base_move(100, 90, -40, 1800), Intake_Event::intake_stationary(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_right_two_goals.add_robot_event(Base_Event::base_move(120, 0, 0, 1500), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_right_two_goals.add_robot_event(Base_Event::base_stationary(400), Intake_Event::intake_store(), Lift_Event::lift_score_one());// Wait for score, Store Intakes, Score One Ball

	/* Red Middle Goal */
	l_right_two_goals.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 1200), Intake_Event::intake_store(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_right_two_goals.add_robot_event(Base_Event::base_move(0, 0, -FULL_TURN, 960), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_right_two_goals.add_robot_event(Base_Event::base_move(150, 270, 0, 2550), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_right_two_goals.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 0, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_right_two_goals.add_robot_event(Base_Event::base_stationary(SCORE_TIME), Intake_Event::intake_store(), Lift_Event::lift_score_one());

	l_right_two_goals.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 1000), Intake_Event::intake_stationary(), Lift_Event::lift_stationary());
}

void define_red_right_corner(Robot& p_robot){
	Autonomous_Routine& l_right_corner = p_robot.get_autonomous().add_autonomous_routine("Red_Right_Corner", ROBOT_RED);

	/* Red Corner Goal */
	l_right_corner.add_robot_event(Base_Event::base_move(100, 90, -40, 1800), Intake_Event::intake_stationary(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_right_corner.add_robot_event(Base_Event::base_move(120, 0, 0, 1500), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_right_corner.add_robot_event(Base_Event::base_stationary(400), Intake_Event::intake_store(), Lift_Event::lift_score_one());// Wait for score, Store Intakes, Score One Ball
	l_right_corner.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 1200), Intake_Event::intake_stationary(), Lift_Event::lift_stationary());
}

/* Blue Autonomous Routines */
void define_blue_corner_and_center(Robot& p_robot){
	Autonomous_Routine& blue_corner_and_center = p_robot.get_autonomous().add_autonomous_routine("Blue_Corner_and_Center", ROBOT_BLUE);

	/* Red Corner Goal */
	blue_corner_and_center.add_robot_event(Base_Event::base_move(100, 270, 40, 1800), Intake_Event::intake_stationary(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	blue_corner_and_center.add_robot_event(Base_Event::base_move(120, 0, 0, 1500), Intake_Event::intake_store(), Lift_Event::lift_sort());
	blue_corner_and_center.add_robot_event(Base_Event::base_stationary(400), Intake_Event::intake_store(), Lift_Event::lift_score_one());// Wait for score, Store Intakes, Score One Ball

	/* Center Goal Ball */
	blue_corner_and_center.add_robot_event(Base_Event::base_move(150, 180, 0, 1600), Intake_Event::intake_goal(), Lift_Event::lift_sort());
	blue_corner_and_center.add_robot_event(Base_Event::base_move(0, 0, -FULL_TURN, 2050), Intake_Event::intake_grab(INTAKE_RETRACT_OPEN), Lift_Event::lift_sort());
	blue_corner_and_center.add_robot_event(Base_Event::base_move(150, 0, 0, 1500), Intake_Event::intake_grab(INTAKE_RETRACT_NONE), Lift_Event::lift_sort());

	/* Center Goal */
	blue_corner_and_center.add_robot_event(Base_Event::base_move(150, 275, 0, 1700), Intake_Event::intake_stationary(), Lift_Event::lift_sort());
	blue_corner_and_center.add_robot_event(Base_Event::base_move(115, 180, 0, 950), Intake_Event::intake_stationary(), Lift_Event::lift_sort());
	blue_corner_and_center.add_robot_event(Base_Event::base_move(100, 300, 17, 1700), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort());
	blue_corner_and_center.add_robot_event(Base_Event::base_stationary(3000), Intake_Event::intake_stationary(), Lift_Event::lift_score_one());
}

void define_blue_left_two_goals(Robot& p_robot){
	Autonomous_Routine& l_left_two_goals = p_robot.get_autonomous().add_autonomous_routine("Blue_Left_Two_Goals", ROBOT_BLUE);

	/* Red Corner Goal */
	l_left_two_goals.add_robot_event(Base_Event::base_move(100, 270, 40, 1800), Intake_Event::intake_stationary(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_left_two_goals.add_robot_event(Base_Event::base_move(120, 0, 0, 1400), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_left_two_goals.add_robot_event(Base_Event::base_stationary(400), Intake_Event::intake_store(), Lift_Event::lift_score_one());// Wait for score, Store Intakes, Score One Ball

	/* Red Middle Goal */
	l_left_two_goals.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 1200), Intake_Event::intake_store(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_left_two_goals.add_robot_event(Base_Event::base_move(0, 0, FULL_TURN, 950), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_left_two_goals.add_robot_event(Base_Event::base_move(150, 90, 0, 2600), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_left_two_goals.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 0, 0, 900), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_left_two_goals.add_robot_event(Base_Event::base_stationary(SCORE_TIME), Intake_Event::intake_store(), Lift_Event::lift_score_one());

	l_left_two_goals.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 1000), Intake_Event::intake_stationary(), Lift_Event::lift_stationary());
}

void define_blue_right_two_goals(Robot& p_robot){
	Autonomous_Routine& l_right_two_goals = p_robot.get_autonomous().add_autonomous_routine("Blue_Right_Two_Goals", ROBOT_BLUE);

	/* Red Corner Goal */
	l_right_two_goals.add_robot_event(Base_Event::base_move(100, 90, -40, 1800), Intake_Event::intake_stationary(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_right_two_goals.add_robot_event(Base_Event::base_move(120, 0, 0, 1500), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_right_two_goals.add_robot_event(Base_Event::base_stationary(400), Intake_Event::intake_store(), Lift_Event::lift_score_one());// Wait for score, Store Intakes, Score One Ball

	/* Red Middle Goal */
	l_right_two_goals.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 1200), Intake_Event::intake_store(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_right_two_goals.add_robot_event(Base_Event::base_move(0, 0, -FULL_TURN, 950), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_right_two_goals.add_robot_event(Base_Event::base_move(150, 270, 0, 2600), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_right_two_goals.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 0, 0, 900), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_right_two_goals.add_robot_event(Base_Event::base_stationary(SCORE_TIME), Intake_Event::intake_store(), Lift_Event::lift_score_one());

	l_right_two_goals.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 1000), Intake_Event::intake_stationary(), Lift_Event::lift_stationary());
}

void define_blue_right_corner(Robot& p_robot){
	Autonomous_Routine& l_right_corner = p_robot.get_autonomous().add_autonomous_routine("Blue_Right_Corner", ROBOT_BLUE);

	/* Red Corner Goal */
	l_right_corner.add_robot_event(Base_Event::base_move(100, 90, -40, 1800), Intake_Event::intake_stationary(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_right_corner.add_robot_event(Base_Event::base_move(120, 0, 0, 1500), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_right_corner.add_robot_event(Base_Event::base_stationary(400), Intake_Event::intake_store(), Lift_Event::lift_score_one());// Wait for score, Store Intakes, Score One Ball
	l_right_corner.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 1200), Intake_Event::intake_stationary(), Lift_Event::lift_stationary());
}


/* Skills Routines */
void define_skills(Robot& p_robot){
	Autonomous_Routine& l_skills = p_robot.get_autonomous().add_autonomous_routine("Skills", ROBOT_SKILLS);
	

	/* Lower Right Goal */
	l_skills.add_robot_event(Base_Event::base_stationary(700), Intake_Event::intake_goal(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(94.5, 0, 75, 2400), Intake_Event::intake_store(500), Lift_Event::lift_sort_and_shoot(2000));// Turn base to goal, Pick up ball in front and then store, Preload the balls

	/* Middle Right Goal */
	l_skills.add_robot_event(Base_Event::base_move(150, 180, 0, 1000), Intake_Event::intake_store(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_orientate_to(174.5), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(150, 89, -1, 2640), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(150, 0, 0, 730), Intake_Event::intake_store(), Lift_Event::lift_sort_and_shoot(320));

	/* Top Right Goal */
	l_skills.add_robot_event(Base_Event::base_move(140, 180, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort());// Turn base to goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_orientate_to(224), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(150, 85, 0, 1600), Intake_Event::intake_store(), Lift_Event::lift_sort());// Move Base forward towards goal, Pick up ball in front and then store, Preload the balls
	l_skills.add_robot_event(Base_Event::base_move(100, 0, 0, 3800), Intake_Event::intake_manual(300), Lift_Event::lift_sort_and_shoot(3500));

	/* Top Middle Goal */
	l_skills.add_robot_event(Base_Event::base_move(150, 180, 0, 2300), Intake_Event::intake_goal(1000), Lift_Event::lift_score_one());
	l_skills.add_robot_event(Base_Event::base_orientate_to(354), Intake_Event::intake_stationary(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(150, 0, 0, 1900), Intake_Event::intake_grab(INTAKE_RETRACT_OPEN), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_orientate_to(265), Intake_Event::intake_grab(INTAKE_RETRACT_OPEN), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(125, 0, 0, 2100), Intake_Event::intake_grab(INTAKE_RETRACT_STORE), Lift_Event::lift_sort_and_shoot(1700));

	/* Top Left Goal */
	l_skills.add_robot_event(Base_Event::base_move(100, 180, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_orientate_to(354), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(150, 357, 0, 2750), Intake_Event::intake_grab(INTAKE_RETRACT_OPEN), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_orientate_to(312), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(140, 0, 0, 1100), Intake_Event::intake_store(), Lift_Event::lift_sort_and_shoot(500));

	/* Left Middle Goal */
	l_skills.add_robot_event(Base_Event::base_move(130, -135, 0, 900), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_orientate_to(448), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(150, 0, 0, 2950), Intake_Event::intake_manual(0), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_orientate_to(362), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(150, 0, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort_and_shoot(300));

	/* Center Goal */
	l_skills.add_robot_event(Base_Event::base_move(FULL_TRANSLATION, 180, 0, 700), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_orientate_to(185), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(150, 352, 0, 2400), Intake_Event::intake_goal(0), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(0, 0, FULL_TURN, 500), Intake_Event::intake_store(), Lift_Event::lift_sort_and_shoot(50));

	/* Lower Left Goal */
	l_skills.add_robot_event(Base_Event::base_move(150, 180, 0, 1000), Intake_Event::intake_goal(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_orientate_to(58), Intake_Event::intake_store(), Lift_Event::lift_sort());
	l_skills.add_robot_event(Base_Event::base_move(130, 8, 0, 3500), Intake_Event::intake_goal(700), Lift_Event::lift_sort_and_shoot(3000));

	/* Lower Middle Goal */
	l_skills.add_robot_event(Base_Event::base_move(150, 180, 0, 900), Intake_Event::intake_goal(), Lift_Event::lift_sort());
	// l_skills.add_robot_event(Base_Event::base_orientate_to(182), Intake_Event::intake_store(), Lift_Event::lift_sort());
	// l_skills.add_robot_event(Base_Event::base_move(150, 5, 0, 2900), Intake_Event::intake_manual(1500), Lift_Event::lift_sort());
	// l_skills.add_robot_event(Base_Event::base_orientate_to(88), Intake_Event::intake_store(), Lift_Event::lift_sort());
	// l_skills.add_robot_event(Base_Event::base_move(150, 0, 0, 500), Intake_Event::intake_store(), Lift_Event::lift_sort_and_shoot(100));// Wait for score, Store Intakes, Score One Ball

	// p_robot.set_robot_alliance(ROBOT_SKILLS);
	// p_robot.get_autonomous().set_selected_routine("Skills");
}

void define_odometry(Robot& p_robot){
	Autonomous_Routine& odometry = p_robot.get_autonomous().add_autonomous_routine("Odometry", ROBOT_SKILLS);

	odometry.add_robot_event(Base_Event::base_orientate_to(-90), Intake_Event::intake_stationary(), Lift_Event::lift_stationary());// Turn base to goal, Pick up ball in front and then store, Preload the balls
}

void Robot::define_autonomous_routines(){
	/* Red Autonomous Routines */
	define_red_corner_and_center(*this);
	define_red_left_two_goals(*this);
	define_red_right_two_goals(*this);
	define_red_right_corner(*this);

	/* Blue Autonomous Routines */
	define_blue_corner_and_center(*this);
	define_blue_left_two_goals(*this);
	define_blue_right_two_goals(*this);
	define_blue_right_corner(*this);

	/* Skills Autonomous Routines */
	define_skills(*this);
	define_odometry(*this);

	
}