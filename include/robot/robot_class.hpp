#include "robot/robot_main.hpp"
#include "robot/devices/data_storage_class.hpp"
#include "robot/subsystems/base_class.hpp"
#include "robot/graphical_interface/screen_class.hpp"


#ifndef ROBOT_CLASS_H
#define ROBOT_CLASS_H
class Robot{
private:
  bool m_recall_settings{};

  Robot_State m_robot_state;

  CONTROLLER::Controller& m_main_controller;
	CONTROLLER::Controller& m_partner_controller;

  Holonomic m_base{*this};

  std::vector<Motor*> m_motor_list{};
  std::vector<SENSOR::Distance*> m_distance_list{};
  std::vector<SENSOR::Rotation*> m_rotation_list{};
  std::vector<SENSOR::Optical*> m_optical_list{};
  std::vector<SENSOR::Digital*> m_digital_list{};

  Data_Storing m_settings{"Settings.xml", "Robot", "1069B"};
public:
  /*  Constuctors  */
  Robot();
  /*  Getting Function  */
  bool get_recall_settings(){ return m_recall_settings; }

  Robot_State get_robot_state(){ return m_robot_state; }

  CONTROLLER::Controller& get_main_controller(){ return m_main_controller; } 

  CONTROLLER::Controller& get_partner_controller(){ return m_partner_controller; }

  /*  Setter Function  */
  void set_robot_state(Robot_State p_state){ m_robot_state = p_state; }

  /* Creation Functions */
  Motor& add_motor(std::string const p_name, short const p_port, pros::motor_gearset_e_t const p_gearset, pros::motor_brake_mode_e_t const p_brake, bool const p_reversed);

  SENSOR::Distance& add_distance(std::string const p_name, short const p_port);

  SENSOR::Rotation& add_rotation(std::string const p_name, short const p_port, bool const p_reversed, int const p_position_offset = 0);

  SENSOR::Optical& add_optical(std::string const p_name, short const p_port, short const p_pwm_value);

  SENSOR::Digital& add_digital(std::string const p_name, short const p_port);
  /* Finder Functions */
  Motor& find_motor(std::string const p_name);

  /*  Action Functions */
  void task();

  void defineGUI();

};

#endif // ROBOT_CLASS_H
