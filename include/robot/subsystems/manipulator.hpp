#include "robot/robot_main.hpp"

#ifndef MANIPULATOR_CLASS_H
#define MANIPULATOR_CLASS_H
class Manipulator{
private:
    Robot& m_robot;

    Motor& m_left_intake;
    Motor& m_right_intake;

    Motor& m_initial_roller;
    Motor& m_secondary_roller;

    SENSOR::Optical& m_intake_sensor;
    SENSOR::Optical& m_sorting_sensor;

    SENSOR::Analog_Pair& m_tongue_sensor;

    SENSOR::Distance& m_scoring_sensor;

    SENSOR::Digital& m_left_intake_sensor;
    SENSOR::Digital& m_right_intake_sensor;


    Intake_Status m_intake_status = INTAKE_STATIONARY;
    Intake_Retract_Mode m_intake_retract = INTAKE_RETRACT_OPEN;
    bool m_intake_drivers = false;

    Lift_Status m_shooting_status = LIFT_STATIONARY;
    bool m_lift_drivers = false;
    Ball_Position m_ball_positions;

    Timer& m_intake_timer;
    Timer& m_lift_timer;

    /*Autonomous*/
    Autonomous_Intake_Status m_autonomous_intake_status;
    Autonomous_Lift_Status m_autonomous_lift_status;

    void set_intake_velocities(int const p_left_velocity, int const p_right_velocity);
    void set_intake_velocities(int const p_velocity){ set_intake_velocities(p_velocity, p_velocity); };

    void intake_auto_grabbing();
    void intake_scoring();
    void intake_store();

    void manipulator_sorting();
    void manipulator_scoring();

    /* Robot State Functions */
    void autonomous();

    void driver_control();

    friend class Autonomous_Routine;
public:
    /* Constructors */
    Manipulator(Robot& p_robot);

    /* Setter Functions */
    void set_intake_retract(Intake_Retract_Mode p_intake_retract){ m_intake_retract = p_intake_retract; };

    void set_autonomous_intake_status(Autonomous_Intake_Status p_autonomous_intake_status, Intake_Retract_Mode p_intake_retract);
    
    void set_autonomous_lift_status(Autonomous_Lift_Status p_autonomous_lift_status);

    bool is_scoring();
    /* Action Functions */
    void initialize();
    
    void task();

    void define_GUI();
};

#endif // MANIPULATOR_CLASS_H