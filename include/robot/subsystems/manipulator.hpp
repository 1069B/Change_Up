#include "robot/robot_main.hpp"

#ifndef MANIPULATOR_CLASS_H
#define MANIPULATOR_CLASS_H

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
    LIFT_SENSORS
};

enum Intake_Position{
    INTAKE_FULLY_EXTENDED,
    INTAKE_OPEN,
    INTAKE_STORED
};

enum Ball{
    BALL_DESIRED,
    BALL_OPPOSING,
    BALL_GOAL,
    BALL_NONE
};

struct Ball_Position{
public:
    Ball m_intakes = BALL_NONE;
    Ball m_sorting = BALL_NONE;
    Ball m_scoreing = BALL_NONE;
};

class Manipulator{
private:
    Robot& m_robot;

    Motor& m_left_intake;
    Motor& m_right_intake;

    Motor& m_initial_roller;
    Motor& m_secondary_roller;

    SENSOR::Optical& m_intake_sensor;
    SENSOR::Optical& m_sorting_sensor;

    SENSOR::Digital& m_scoring_left_sensor;
    SENSOR::Digital& m_scoring_right_sensor;

    Timer& m_timer;

    Intake_Status m_intake_status = INTAKE_STATIONARY;
    Lift_Status m_lift_status = LIFT_NO_RESTRICTIONS;

    Ball_Position m_ball_positions;
    Intake_Position m_intake_position;

    Timer& m_intake_timer;
    Timer& m_lift_timer;

    /* Robot State Functions */
    void initialize();

    void autonomous();

    void driver_control();

    void feild_grabing();

    void goal_controlling();

public:
    /* Constructors */
    Manipulator(Robot& p_robot);

    /* Action Functions */
    void task();

    void define_GUI();
};

#endif // MANIPULATOR_CLASS_H