#include "robot/robot_main.hpp"
#include "robot/devices/data_storage_class.hpp"

#ifndef INERTIAL_CLASS_H
#define INERTIAL_CLASS_H

namespace SENSOR{
  class Inertial{
  private:
    Robot& m_robot;

    /*Settings*/
    std::string m_name{};
    short m_port{};

    double m_pitch_offset{};
    double m_roll_offset{};
    double m_yaw_offset{};

    std::vector<double> m_average_pitch_vector;
    std::vector<double> m_average_roll_vector;
    std::vector<double> m_average_yaw_vector;

    std::vector<double> m_average_pitch_acceleration_vector;
    std::vector<double> m_average_roll_acceleration_vector;
    std::vector<double> m_average_yaw_acceleration_vector;

    Data_Storing m_settings;

    double running_average(std::vector<double>& p_vector);
    double store_running_value(double const p_value, std::vector<double>& p_vector);
  public:
    /*  Constuctors  */
    Inertial(Robot &p_robot, std::string const p_name, short const p_port);

    /*  Getting Functions  */
    std::string get_name(){ return m_name; }

    short get_port(){ return m_port; }

    double get_pitch(){ return store_running_value(pros::c::imu_get_pitch(m_port) + m_pitch_offset, m_average_pitch_vector); }

    double get_roll(){ return store_running_value(pros::c::imu_get_roll(m_port) + m_roll_offset, m_average_roll_vector); }

    double get_yaw(){ return store_running_value(pros::c::imu_get_yaw(m_port) + m_yaw_offset, m_average_yaw_vector); }

    double get_average_pitch(){ return running_average(m_average_pitch_vector); }

    double get_average_roll(){ return running_average(m_average_roll_vector); }

    double get_average_yaw(){ return running_average(m_average_yaw_vector); }

    double get_pitch_rate();

    double get_roll_rate();

    double get_yaw_rate();

    double get_pitch_acceleration();

    double get_roll_acceleration();

    double get_yaw_acceleration();

    double get_average_pitch_acceleration(){ return running_average(m_average_pitch_acceleration_vector); }

    double get_average_roll_acceleration(){ return running_average(m_average_roll_acceleration_vector); }

    double get_average_yaw_acceleration(){ return running_average(m_average_yaw_acceleration_vector); }

    bool is_calibrating();

    /* Setter Functions */
    void set_pitch_offset(double const p_pitch_offset){ m_pitch_offset = p_pitch_offset; };

    void set_roll_offset(double const p_roll_offset){ m_roll_offset = p_roll_offset; };

    void set_yaw_offset(double const p_yaw_offset){ m_yaw_offset = p_yaw_offset; };

    /* Action Functions */
    void calibrate();

    /* Setter Function*/
    void set_port(short const p_port);
  };
}

#endif// INERTIAL_CLASS_H
