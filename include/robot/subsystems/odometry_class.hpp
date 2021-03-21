#include "robot/robot_main.hpp"

#ifndef ODOMETRY_CLASS_H
#define ODOMETRY_CLASS_H

class Odometry{
private:
    std::string m_name = "Odometry";
    Robot& m_robot;

    SENSOR::Rotation& m_left_encoder;
    SENSOR::Rotation& m_center_encoder;
    SENSOR::Rotation& m_right_encoder;

    /* Settings */
    double m_tracking_wheel_distance = 25.5587; //TODO Refine Vale
    double m_tracking_wheel_circumference = 22.11; //TODO Refine Vale

    /* Orientation Variables */
    double m_total_orientation = 0;
    double m_terminal_orientation = 0;

    double m_orientation_velocity = 0;

    Timer& m_orientation_timer;
    double m_orientation_cycle_time;

    Data_Logging& m_odometry_debug;

    /* Relative Translations */
    double m_left_encoder_velocity;
    double m_right_encoder_velocity;

    double m_left_encoder_displacement;
    double m_right_encoder_displacement;

    double m_x_relative_position;
    double m_y_relative_position;

    double m_x_relative_velocity;
    double m_y_relative_velocity;

    Timer& m_relative_translation_timer;
    double m_relative_translation_cycle_time;

    /* Absolute Translation */
    double m_x_absolute_position;
    double m_y_absolute_position;

    double m_x_absolute_velocity;
    double m_y_absolute_velocity;

    /*Member Functions*/
    double total_angle_to_terminal_angle(double p_angle);

    double radian_to_degree(double p_radian);
    double degree_to_radian(double p_degree);

    void orientation_calculation();

    void translation_calculation();

public:
    /* Constructors */
    Odometry(Robot& p_robot);

    /* Getter Functions: Orientation*/
    double get_total_orientation(){ return m_total_orientation; }

    double get_terminal_orientation(){ return m_terminal_orientation; }

    double get_orientation_velocity(){ return m_orientation_velocity; }

    /* Getter Functions: Relative Translation*/
    double get_x_relative_position(){ return m_x_relative_position; }

    double get_y_relative_postion(){ return m_y_relative_position; }

    double get_x_relative_velocity(){ return m_x_relative_velocity; }

    double get_y_relative_velocity(){ return m_y_relative_velocity; }

    /* Getter Functions: Absolute Translation*/
    double get_x_absolute_position(){ return m_x_absolute_position; }

    double get_y_absolute_postion(){ return m_y_absolute_position; }

    double get_x_absolute_velocity(){ return m_x_absolute_velocity; }

    double get_y_absolute_velocity(){ return m_y_absolute_velocity; }


    /* Setter Functions */
    void set_orientation(double p_orientation);

    void reset_orientation(){ set_orientation(0); }

    void set_absolute_position(double p_x_position, double p_y_position);

    void reset_position(){ set_absolute_position(0, 0); }

    /* Action Functions */
    void initialize();
    
    void task();

    void define_GUI();    
};
#endif // ODOMETRY_CLASS_H