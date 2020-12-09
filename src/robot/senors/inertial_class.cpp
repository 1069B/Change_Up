#include "robot/sensors/inertial_class.hpp"
#include "robot/robot_class.hpp"

using namespace SENSOR;

double Inertial::running_average(std::vector<double> &p_vector){
  double l_sum = 0;
  for(int x = 0; x < p_vector.size(); x++){
    l_sum += p_vector.at(x);
  }
  return l_sum/10.0;
}

double Inertial::store_running_value(double const p_value, std::vector<double>& p_vector){
  std::vector<double> l_value_vector;
  for(int x = 1; x < p_vector.size(); x++){
    l_value_vector.push_back(p_vector.at(x));
  }
  l_value_vector.push_back(p_value);
  p_vector = l_value_vector;
  return p_value;
}


Inertial::Inertial(Robot &p_robot, std::string const p_name, short const p_port):
m_robot(p_robot),
m_settings("Settings.xml", "Inertial", p_name),
m_average_pitch_vector(10,0),
m_average_roll_vector(10,0),
m_average_yaw_vector(10,0),
m_average_pitch_acceleration_vector(10,0),
m_average_roll_acceleration_vector(10,0),
m_average_yaw_acceleration_vector(10,0)
{
  if(m_robot.get_recall_settings()){
    m_name = p_name;
    m_port = m_settings.initialize_int("Port", p_port);
  }
  else{
    m_name = p_name;
    m_port = p_port;
  }
}

/*  Getting Functions  */


double Inertial::get_pitch_rate(){
  pros::c::imu_gyro_s_t l_gyro = pros::c::imu_get_gyro_rate(m_port);
  return l_gyro.y;
}

double Inertial::get_roll_rate(){
  pros::c::imu_gyro_s_t l_gyro = pros::c::imu_get_gyro_rate(m_port);
  return l_gyro.x;
}

double Inertial::get_yaw_rate(){
  pros::c::imu_gyro_s_t l_gyro = pros::c::imu_get_gyro_rate(m_port);
  return l_gyro.z;
}

double Inertial::get_pitch_acceleration(){
  pros::c::imu_accel_s_t l_accel = pros::c::imu_get_accel(m_port);
  return store_running_value(l_accel.y, m_average_pitch_acceleration_vector);
}

double Inertial::get_roll_acceleration(){
  pros::c::imu_accel_s_t l_accel = pros::c::imu_get_accel(m_port);
  return store_running_value(l_accel.x, m_average_roll_acceleration_vector);
}

double Inertial::get_yaw_acceleration(){
  pros::c::imu_accel_s_t l_accel = pros::c::imu_get_accel(m_port);
  return store_running_value(l_accel.z, m_average_yaw_acceleration_vector);
}

bool Inertial::is_calibrating(){
  if(pros::c::imu_get_status(m_port) & pros::c::E_IMU_STATUS_CALIBRATING)
    return true;
  return false;
}

/* Setter Function */
void Inertial::set_port(short const p_port){
  m_port = p_port;
  m_settings.store_int("Port", m_port);
}
