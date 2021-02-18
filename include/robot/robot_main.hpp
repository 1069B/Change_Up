#include "main.h"
#include "robot/graphical_interface/styles.hpp"
//#include "robot/graphical_interface/alertClass.hpp"

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
class Manipulator;
class Autonomous_Routine;


/* Enum Variables*/

enum Robot_State{
  ROBOT_INITIALIZATION,
  ROBOT_DRIVER_CONTROL,
  ROBOT_AUTONOMOUS,
  ROBOT_DISABLED
};

enum Robot_Alliance{
  ROBOT_BLUE,
  ROBOT_RED,
  ROBOT_SKILLS
};

enum Intake_Status{
  INTAKE_AUTO_INTAKE,
  INTAKE_AUTO_OPEN,
  INTAKE_STATIONARY
};

enum Lift_Status{
  LIFT_SCORING,
  LIFT_WAITING,
  LIFT_STATIONARY
};

enum Ball{
  BALL_DESIRED,
  BALL_OPPOSING,
  BALL_NONE
};

enum Intake_Retract_Mode{
  INTAKE_RETRACT_NONE,
  INTAKE_RETRACT_OPEN,
  INTAKE_RETRACT_STORE
};
struct Ball_Position{
public:
  Ball m_intakes = BALL_NONE;
  Ball m_tongue = BALL_NONE;
  Ball m_sorting = BALL_NONE;
  Ball m_scoreing = BALL_NONE;
};

extern bool outside_range(double const p_value, double const p_range);

#endif // MAIN_HEADER