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
class Autonomous;


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
    INTAKE_INTAKING,
    INTAKE_AUTO_INTAKE,
    INTAKE_AUTO_OPEN,
    INTAKE_OPENING,
    INTAKE_STATIONARY,
    INTAKE_USER_BASED
};

enum Lift_Status{
    LIFT_TOP_CONTROLLED,
    LIFT_BOTH_CONTROLLED,
    LIFT_NO_RESTRICTIONS,
    LIFT_INTAKING,
    LIFT_SENSORS, 
    LIFT_SCORING,
    LIFT_WAITING,
    LIFT_STATIONARY,
    LIFT_COMPLETE
};

enum Intake_Position{
    INTAKE_FULLY_EXTENDED,
    INTAKE_OPEN,
    INTAKE_STORED
};

enum Ball{
    BALL_DESIRED,
    BALL_OPPOSING,
    BALL_NONE
};

enum Manipulator_Mode{
    MANIPULATOR_FEILD,
    MANIPULATOR_SCORE
};

enum Manipulator_Intake_Mode{
    MANIPULATOR_INTAKE_SENSOR,
    MANIPULATOR_INTAKE_DEPLOY,
    MANIPULATOR_INTAKE_STORE
};

#endif // MAIN_HEADER