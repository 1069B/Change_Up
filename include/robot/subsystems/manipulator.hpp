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
    LIFT_INTAKING,
    LIFT_SCORING,
    LIFT_EJECTING,
    LIFT_STATIONARY,
    LIFT_USER_BASED
};

class Manipulator{
private:
    Robot& m_robot;

    Motor& m_left_intake;
    Motor& m_right_intake;

    Motor& m_initial_roller;
    Motor& m_secondary_roller;

    Timer& m_timer;

    Intake_Status m_intake_status = INTAKE_STATIONARY;
    Lift_Status m_lift_status = LIFT_STATIONARY;

    /* Robot State Functions */
    void initialize();

    void autonomous();

    void driver_control();

public:
    /* Constructors */
    Manipulator(Robot& p_robot);

    /* Action Functions */
    void task();

    void define_GUI();
};

#endif // MANIPULATOR_CLASS_H