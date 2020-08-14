#include "main.h"
#include "robot/graphical_interface/rectangle_class.hpp"
#include "robot/graphical_interface/label_class.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {


	static lv_style_t style_txt;
	lv_style_copy(&style_txt, &lv_style_plain);
	//style_txt.text.font = &lv_font_dejavu_40;
	style_txt.text.letter_space = 2;
	style_txt.text.line_space = 1;
	style_txt.text.color = LV_COLOR_HEX(0xFF0000);


	Rectangle header_rectangle{};
	header_rectangle.set_xOrgin(20);
	header_rectangle.set_yOrgin(20);
	header_rectangle.set_legnth(200);
	header_rectangle.set_width(50);
	header_rectangle.set_style(lv_style_plain);

	//header_rectangle.draw_rectangle();

	int test = 5;

	Label<int*> basic_label{};
	basic_label.set_xOrgin(20);
	basic_label.set_yOrgin(100);
	basic_label.set_text("Hello I am %p years old");
	basic_label.set_dynamic_functionality(&test);
	basic_label.set_style(style_txt);

	basic_label.draw_label();
	test = 10;
	pros::delay(2000);
	basic_label.update_label();

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
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;
		pros::delay(20);
	}
}
