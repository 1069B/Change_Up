#include "robot/robot_main.hpp"

#ifndef ROBOT_CLASS_H
#define ROBOT_CLASS_H

class Robot{
private:
  bool m_recall_settings{};

  Robot_State m_robot_state;

  CONTROLLER::Controller& m_main_controller;
	CONTROLLER::Controller& m_partner_controller;

  Holonomic& m_holonomic;
  Manipulator& m_manipulator;

  std::vector<Motor*> m_motor_list{};
  std::vector<SENSOR::Distance*> m_distance_list{};
  std::vector<SENSOR::Rotation*> m_rotation_list{};
  std::vector<SENSOR::Optical*> m_optical_list{};
  std::vector<SENSOR::Digital*> m_digital_list{};
  std::vector<SENSOR::Analog_Pair*> m_analog_pair_list{};

  std::vector<Autonomous_Routine*> m_autonomous_routines{};

  Data_Storing& m_settings;

  Robot_Alliance m_alliance = ROBOT_SKILLS;// TODO: ADD GUI SETTING

  void define_autonomous_routines();
public:
  /*  Constuctors  */
  Robot();
  /*  Getting Function  */
  bool get_recall_settings(){ return m_recall_settings; }

  Robot_State get_robot_state(){ return m_robot_state; }

  CONTROLLER::Controller& get_main_controller(){ return m_main_controller; } 

  CONTROLLER::Controller& get_partner_controller(){ return m_partner_controller; }

  Robot_Alliance get_alliance(){ return m_alliance; }

  Holonomic& get_holonomic(){ return m_holonomic; }

  Manipulator& get_manipulator(){ return m_manipulator; }

  /*  Setter Function  */
  void set_robot_state(Robot_State p_state){ m_robot_state = p_state; }

  /* Creation Functions */
  Motor& add_motor(std::string const p_name, short const p_port, pros::motor_gearset_e_t const p_gearset, pros::motor_brake_mode_e_t const p_brake, bool const p_reversed);

  SENSOR::Distance& add_distance(std::string const p_name, short const p_port);

  SENSOR::Rotation& add_rotation(std::string const p_name, short const p_port, bool const p_reversed, int const p_position_offset = 0);

  SENSOR::Optical& add_optical(std::string const p_name, short const p_port, short const p_pwm_value = 0);

  SENSOR::Digital& add_digital(std::string const p_name, short const p_port);

  SENSOR::Analog_Pair& add_analog_pair(std::string const p_name, short const p_expander_port, short const p_first_port, short const p_second_port, double p_lower_bound, double p_upper_bound);

  Autonomous_Routine& add_autonomous_routine(std::string p_routine_name, Robot_Alliance p_routine_alliance);
  /* Finder Functions */
  Motor& find_motor(std::string const p_name);

  /*  Action Functions */
  void initialize();

  void task();

  void defineGUI();
};

#endif // ROBOT_CLASS_H
