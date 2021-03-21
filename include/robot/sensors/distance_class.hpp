#include "robot/robot_main.hpp"

#ifndef DISTANCE_CLASS_H
#define DISTANCE_CLASS_H
namespace SENSOR{
  class Distance{
  private:
    Robot& m_robot;

    /*Settings*/
    std::string m_name{};
    short m_port{};

    std::vector<int> m_average_distance_vector{1000,1000,1000,1000,1000};

    Data_Storing& m_settings;
  public:
    /*  Constuctors  */
    Distance(Robot &p_robot, std::string const p_name, short const p_port);

    /*  Getting Functions  */
    std::string get_name(){ return m_name; }

    short get_port(){ return m_port; }

    int get_distance();

    int get_average_distance();

    int get_confidence(){ return pros::c::distance_get_confidence(m_port); };

    int get_object_size(){ return pros::c::distance_get_object_size(m_port); };

    int get_object_velocity(){ return pros::c::distance_get_object_velocity(m_port); };

    /* Setter Function*/
    void set_port(short const p_port);
  };
}

#endif // DISTANCE_CLASS_H
