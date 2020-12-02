#include "robot/robot_main.hpp"
#include "robot/devices/data_storage_class.hpp"

#ifndef DISTANCE_CLASS_H
#define DISTANCE_CLASS_H

namespace SENSOR{
  class Distance{
  private:
    Robot& m_robot;

    /*Settings*/
    std::string m_name{};
    short m_port{};

    Data_Storing m_settings;
  public:
    /*  Constuctors  */
  Distance(Robot &p_robot, std::string const p_name, short const p_port);

  /*  Getting Functions  */
  std::string get_name(){ return m_name; }

  short get_port(){ return m_port; }


  int get_distance(){ return pros::c::distance_get(m_port) };

  int get_confidence( return pros::c::);

  int get_object_size( return pros::c::);

  int get_object_velocity( return pros::c::);

  /* Setter Function*/
  void set_port(short const p_port);


distance_get_confidence
distance_get_object_size
distance_get_object_velocity
  };
}

#endif // MOTOR_CLASS_H
