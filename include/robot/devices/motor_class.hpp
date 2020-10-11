#include "main.h"

#ifndef MOTOR_CLASS_H
#define MOTOR_CLASS_H

class Motor{
private:
  short m_port{};

  bool m_reversed{false};

  pros::motor_brake_mode_e_t m_brake_mode{};

  pros::motor_gearset_e_t m_motor_gearset{};

  int m_desiredVelocity;
  
  int m_desiredVoltage;
public:
  /*  Constuctors  */
  Motor();
  /*  Getting Function  */

  /*  Setter Function  */

  /*  Action Functions */

};


#endif // MOTOR_CLASS_H
