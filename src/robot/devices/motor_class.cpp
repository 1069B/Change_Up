#include "robot/devices/motor_class.hpp"
#include "robot/robot_class.hpp"

Motor::Motor(Robot &p_robot, std::string const p_name, short const p_port, pros::motor_gearset_e_t const p_motor_gearset, pros::motor_brake_mode_e_t const p_motor_brake, bool const p_reversed):
m_robot(p_robot){
  if(m_robot.get_recall_settings()){
    m_port = m_settings.intitialize_int("Port", p_port);
    m_motor_gearset = (pros::motor_gearset_e_t)m_settings.intitialize_int("Gearset", (int)p_motor_gearset);
    m_brake_mode = (pros::motor_brake_mode_e_t)m_settings.intitialize_int("Brake", (int)p_motor_brake);
    m_reversed = m_settings.intitialize_bool("Reversed", p_reversed);
  }
  else{
    m_name = p_name;
    m_port = p_port;
    m_motor_gearset = p_motor_gearset;
    m_reversed = p_reversed;
  }

  pros::c::motor_set_gearing(m_port, m_motor_gearset);
  pros::c::motor_set_brake_mode(m_port, m_brake_mode);
  pros::c::motor_set_reversed(m_port, m_reversed);
  pros::c::motor_set_encoder_units(m_port, pros::E_MOTOR_ENCODER_ROTATIONS);


}

/* Setter Function */
void Motor::set_port(short const p_port){
  m_port = p_port;
  m_settings.store_int("Port", m_port);
}

void Motor::set_reversed(bool const p_reversed){
  m_reversed = p_reversed;
  m_settings.store_bool("Reversed", m_reversed);
}

void Motor::set_brake_mode(pros::motor_brake_mode_e_t const p_brake_mode){
  m_brake_mode = p_brake_mode;
  m_settings.store_int("Brake", m_brake_mode);
}

void Motor::set_motor_gearset(pros::motor_gearset_e_t const p_motor_gearset){
  m_motor_gearset = p_motor_gearset;
  m_settings.store_int("Gearset", m_motor_gearset);
  pros::c::motor_set_gearing(m_port, m_motor_gearset);
}

void Motor::set_desired_velocity(int const p_desired_velocity){
  m_desired_velocity = p_desired_velocity;
  m_mode = MOTOR_VELOCITY_DEPENDENT;
  m_desired_voltage = 0;
  pros::c::motor_move_velocity(m_port, m_desired_velocity);
}

void Motor::set_desired_voltage(int const p_desired_voltage){
  m_desired_voltage = p_desired_voltage;
  m_mode = MOTOR_VOLTAGE_DEPENDENT;
  m_desired_velocity = 0;
  pros::c::motor_move_voltage(m_port, m_desired_voltage);
}
