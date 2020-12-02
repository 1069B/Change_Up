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

    int m_pitch_offset{};
    int m_roll_offset{};
    int m_yaw_offset{};

    std::vector<int> m_average_pitch_vector;
    std::vector<int> m_average_roll_vector;
    std::vector<int> m_average_yaw_vector;

    Data_Storing m_settings;
  public:
    /*  Constuctors  */
    Inertial(Robot &p_robot, std::string const p_name, short const p_port);

    /*  Getting Functions  */
    std::string get_name(){ return m_name; }

    short get_port(){ return m_port; }

    int get_pitch();

    int get_roll();

    int get_yaw();

    int get_average_pitch();

    int get_average_roll();

    int get_average_yaw();

    int get_pitch_rate();

    int get_roll_rate();

    int get_yaw_rate();

    int get_pitch_acceleration();

    int get_roll_acceleration();

    int get_yaw_acceleration();

    bool is_calibrating();

    /* Setter Functions */
    void set_pitch_offset(int const p_pitch_offset){ m_pitch_offset = p_pitch_offset; };

    void set_roll_offset(int const p_roll_offset){ m_roll_offset = p_roll_offset; };

    void set_yaw_offset(int const p_yaw_offset){ m_yaw_offset = p_yaw_offset; };

    /* Action Functions */
    void reset();






    /* Setter Function*/
    void set_port(short const p_port);
  };
}

#endif// INERTIAL_CLASS_H
