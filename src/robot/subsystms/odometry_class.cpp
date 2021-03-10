#include "robot/devices/timer_class.hpp"
#include "robot/devices/data_logging_class.hpp"

#include "robot/sensors/rotation_class.hpp"

#include "robot/subsystems/odometry_class.hpp"

#include "robot/graphical_interface/screen_class.hpp"
#include "robot/graphical_interface/button_class.hpp"

Odometry::Odometry(Robot& p_robot):
m_robot(p_robot),
m_orientation_timer(*new Timer()),
m_relative_translation_timer(*new Timer()),
m_odometry_debug(*new Data_Logging("Odometry.csv")),
m_left_encoder(*new SENSOR::Rotation(m_robot, "Left_Tracking", 8)),
m_center_encoder(*new SENSOR::Rotation(m_robot, "Center_Tracking", 18)), 
m_right_encoder(*new SENSOR::Rotation(m_robot, "Right_Tracking", 17)){
    m_odometry_debug << "Time, Left Velocity, Right Velocity";
}

double Odometry::total_angle_to_terminal_angle(double p_angle){
    if(0 <= p_angle && p_angle < 360)// Detects if Angle is withen desired bounds
        return p_angle;
    else{// If not calculate angle
        if(fabs(p_angle) / p_angle == -1)// Negative Angle
            return std::fmod(p_angle, 360) + 360;
        else
            return std::fmod(p_angle, 360);
    }
}

double Odometry::radian_to_degree(double p_radian){
    return (p_radian/M_PI)*180.0;
}
double Odometry::degree_to_radian(double p_degree){
    return (p_degree/180.0)*M_PI;
}

void Odometry::orientation_calculation(){
    m_orientation_cycle_time = m_orientation_timer.get_current_lap_time()/1000.0;// Time in secs

    double left_encoder_velocity = m_left_encoder.get_velocity() * m_tracking_wheel_circumference; // Converts Rev/sec to cm/sec
    double right_encoder_velocity = m_right_encoder.get_velocity() * m_tracking_wheel_circumference;

    double left_encoder_displacement = left_encoder_velocity * m_orientation_cycle_time;// cms traveled
    double right_encoder_displacement = right_encoder_velocity * m_orientation_cycle_time;

    m_orientation_velocity = radian_to_degree((left_encoder_displacement-right_encoder_displacement)/(m_tracking_wheel_distance)) / m_orientation_cycle_time;// deg/s
    m_total_orientation += radian_to_degree((left_encoder_displacement-right_encoder_displacement)/(m_tracking_wheel_distance));
    m_terminal_orientation = total_angle_to_terminal_angle(m_total_orientation);

    // m_odometry_debug << std::to_string(pros::millis()) << ", " << std::to_string(left_encoder_velocity) << ", " << std::to_string(right_encoder_velocity);
}

void Odometry::translation_calculation(){
    m_relative_translation_cycle_time = m_relative_translation_timer.get_current_lap_time()/1000.0;// Time in secs

    double left_encoder_velocity = m_left_encoder.get_velocity() * m_tracking_wheel_circumference; // Converts Rev/sec to cm/sec
    double right_encoder_velocity = m_right_encoder.get_velocity() * m_tracking_wheel_circumference;
   
    m_x_relative_velocity = (left_encoder_velocity + right_encoder_velocity)/2.0;// cm/s
    m_y_relative_velocity = m_center_encoder.get_velocity() * m_tracking_wheel_circumference;// cm/s

    m_x_relative_position += m_x_relative_velocity * m_relative_translation_cycle_time;// cms traveled
    m_y_relative_position += m_y_relative_velocity * m_relative_translation_cycle_time;
}

void Odometry::set_absolute_position(double p_x_position, double p_y_position){
    m_x_absolute_position = p_x_position;
    m_y_absolute_position = p_y_position;

    m_x_relative_position = 0;
    m_y_relative_position = 0;
}

void Odometry::set_orientation(double p_orientation){
    m_total_orientation = p_orientation;
    m_terminal_orientation = total_angle_to_terminal_angle(m_total_orientation);
}


void Odometry::define_GUI(){
    GUI::Screen &odometry = GUI::Screen::create_screen("Odometry");
    odometry.create_rectangle(0, 0, 480, 40, GUI_STYLES::white_text);
    odometry.create_label(0, 10, GUI_STYLES::red_text, "Odometry", LV_ALIGN_IN_TOP_MID);

    odometry.create_label(20, 50, GUI_STYLES::white_text, "Absolute Orientation: %d Deg", m_total_orientation);
    odometry.create_label(20, 80, GUI_STYLES::white_text, "Terminal Orientation: %d Deg", m_terminal_orientation);
    odometry.create_label(20, 110, GUI_STYLES::white_text, "Orientation Velocity: %d Deg/sec", m_orientation_velocity);
    odometry.create_label(20, 140, GUI_STYLES::white_text, "Cycle Duration: %d ms", m_orientation_cycle_time);

    GUI::Button& go_back = odometry.create_button("Go Back", 300, 200, 150, 20);
    go_back.add_connected_screen("Home");
}

void Odometry::initialize(){
    reset_orientation();
    reset_position();
}

void Odometry::task(){
    orientation_calculation();
    // translation_calculation();
}