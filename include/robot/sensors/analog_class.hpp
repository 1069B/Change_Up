#include "robot/robot_main.hpp"

#ifndef ANALOG_PAIR_CLASS_H
#define ANALOG_PAIR_CLASS_H

namespace SENSOR{
  class Analog_Pair{
  private:
    Robot& m_robot;

    /*Settings*/
    std::string m_name{};
    short m_expander_port{};
    short m_first_port{};
    short m_second_port{};

    double m_lower_bound;
    double m_upper_bound;

    Data_Storing& m_settings;
  public:
    /*  Constuctors  */
    Analog_Pair(Robot &p_robot, std::string const p_name, short const p_expander_port, short const p_first_port, short const p_second_port, double p_lower_bound, double p_upper_bound);

    /*  Getting Functions  */
    std::string get_name(){ return m_name; }

    short get_first_port(){ return m_first_port; }

    short get_second_port(){ return m_second_port; }

    double get_first_value();

    double get_second_value();

    bool is_both();

    bool is_either();
  };
}

#endif // ANALOG_PAIR_CLASS_H
