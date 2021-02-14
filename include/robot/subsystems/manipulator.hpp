#include "robot/robot_main.hpp"

#ifndef MANIPULATOR_CLASS_H
#define MANIPULATOR_CLASS_H

struct Ball_Position{
public:
    Ball m_intakes = BALL_NONE;
    Ball m_tongue = BALL_NONE;
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

    SENSOR::Distance& m_scoring_sensor;

    SENSOR::Digital& m_left_intake_sensor;
    SENSOR::Digital& m_right_intake_sensor;


    Intake_Status m_intake_status = INTAKE_STATIONARY;
    Lift_Status m_lift_status = LIFT_NO_RESTRICTIONS;

    /* Manipulator States*/
    Ball_Position m_ball_positions;
    Intake_Position m_intake_position = INTAKE_STORED;
    Manipulator_Mode m_mode = MANIPULATOR_FEILD;
    Manipulator_Intake_Mode m_intake_auto_mode = MANIPULATOR_INTAKE_SENSOR;

    Timer& m_intake_timer;
    Timer& m_lift_timer;

    /* Robot State Functions */
    void initialize();

    void autonomous();

    void driver_control();

    void autonomous_feild();

    void autonomous_store_arms();

    void autonomous_deploy_arms();

    void autonomous_score();

public:
    /* Constructors */
    Manipulator(Robot& p_robot);

    /* Setter Functions */
    void set_mode(Manipulator_Mode p_manipulator_mode, Manipulator_Intake_Mode p_intake_mode);

    /* Action Functions */
    void task();

    void define_GUI();
};

#endif // MANIPULATOR_CLASS_H