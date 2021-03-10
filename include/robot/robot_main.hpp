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
  class Analog_Pair;
  class Vision;
}

class Data_Logging;
class Data_Storing;
class Motor;
class Timer;

class Holonomic;
class Manipulator;
class Odometry;

class Autonomous;
class Autonomous_Routine;

/* Enum Variables */
enum Robot_State{
  ROBOT_INITIALIZATION,
  ROBOT_DRIVER_CONTROL,
  ROBOT_AUTONOMOUS,
  ROBOT_DISABLED
};

enum Robot_Alliance{
  ROBOT_BLUE,
  ROBOT_RED,
  ROBOT_SKILLS,
  ROBOT_WAITTING
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

enum Autonomous_Base_Status{
  BASE_TRANSLATE,
  BASE_ORIENTATION,
  BASE_TURN,
  BASE_POSE,
  BASE_ALIGN_GOAL,
  BASE_STATIONARY
};

enum Autonomous_Intake_Status{
  AUTONOMOUS_INTAKE_GRAB,
  AUTONOMOUS_INTAKE_GOAL,
  AUTONOMOUS_INTAKE_STORE,
  AUTONOMOUS_INTAKE_STATIONARY
};

enum Autonomous_Lift_Status{
  AUTONOMOUS_LIFT_SORT,
  AUTONOMOUS_LIFT_SCORE_ONE,
  AUTONOMOUS_LIFT_SCORE_ALL,
  AUTONOMOUS_LIFT_STATIONARY
};

/* Structures */
struct Ball_Position{
public:
  Ball m_intakes = BALL_NONE;
  Ball m_tongue = BALL_NONE;
  Ball m_sorting = BALL_NONE;
  Ball m_scoreing = BALL_NONE;

  Ball m_previous_intakes = BALL_NONE;
};

extern bool outside_range(double const p_value, double const p_range);
extern bool inside_range(double const p_value, double const p_lower_bound, double const p_upper_bound);

#endif // MAIN_HEADER