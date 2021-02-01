#include "main.h"
#include "robot/graphical_interface/styles.hpp"
#include "robot/graphical_interface/alertClass.hpp"

#ifndef MAIN_HEADER
#define MAIN_HEADER

class Robot;

namespace CONTROLLER{
  class Button;
  class Joystick;
  class Controller;
}

/* Graphical User Interface */
namespace GUI{
  class Screen;
  class Rectangle;
  class Roller;
  class Label;
  class Bar;
  class Button;
  class Switch;
}

namespace SENSOR{
  class Optical;
  class Rotation;
  class Distance;
  class Inertial;
  class Digital;
}

class Data_Logging;
class Data_Storing;
class Motor;
class Timer;

class Holonomic;


/* Enum Variables*/

enum Robot_State{
  ROBOT_INITIALIZATION,
  ROBOT_DRIVER_CONTROL,
  ROBOT_AUTONOMOUS,
  ROBOT_DISABLED
};

#endif // MAIN_HEADER