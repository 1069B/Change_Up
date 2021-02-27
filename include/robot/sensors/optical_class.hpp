#include "robot/robot_main.hpp"

#ifndef OPTICAL_CLASS_H
#define OPTICAL_CLASS_H

namespace SENSOR{
  struct Optical_Signature{
  public:
    double m_hue_upper_bound;
    double m_hue_lower_bound;
    double m_saturation_upper_bound;
    double m_saturation_lower_bound;
    int m_proximity;
  };
  class Optical{
  private:
    Robot& m_robot;

    std::string m_name;
    short m_port{};
    short m_pwm_value{};
    
    Optical_Signature m_signature_1;
    Optical_Signature m_signature_2;
    Optical_Signature m_signature_3;

    Data_Storing& m_settings;

    bool is_signature(Optical_Signature& p_signature);

  public:
    //Constructor
    Optical(Robot &p_robot, std::string const p_name, short const p_port, short const p_pwm_value);

    //Getter Functions
    short get_port(){ return m_port; }

    std::string get_name(){ return m_name; }

    double get_hue(){ return pros::c::optical_get_hue(m_port); }

    double get_saturation(){ return pros::c::optical_get_saturation(m_port); }

    double get_brightness(){ return pros::c::optical_get_brightness(m_port); }

    long get_proximity(){ return pros::c::optical_get_proximity(m_port); }

    long get_led_pwm(){ return pros::c::optical_get_led_pwm(m_port); }

    pros::c::optical_rgb_s_t get_rgb(){ return pros::c::optical_get_rgb(m_port); }

    pros::c::optical_raw_s_t get_raw(){ return pros::c::optical_get_raw(m_port); }

    pros::c::optical_direction_e_t get_gesture(){ return pros::c::optical_get_gesture(m_port); }

    pros::c::optical_gesture_s_t get_gesture_raw(){ return pros::c::optical_get_gesture_raw(m_port); }

    Optical_Signature& get_signature_1(){ return m_signature_1; }

    Optical_Signature& get_signature_2(){ return m_signature_2; }

    Optical_Signature& get_signature_3(){ return m_signature_3; }

    //Setter Functions
    void set_led_pwm(short const p_pwm_value);

    void set_port(short const p_port);

    void set_signature_1(double const p_hue_lower_bound, double const p_hue_upper_bound, int p_proximity_thesehold, double const p_saturation_lower_bound = 0.00, double const p_saturation_upper_bound = 1.0);

    void set_signature_2(double const p_hue_lower_bound, double const p_hue_upper_bound, int p_proximity_thesehold, double const p_saturation_lower_bound = 0.00, double const p_saturation_upper_bound = 1.0);

    void set_signature_3(double const p_hue_lower_bound, double const p_hue_upper_bound, int p_proximity_thesehold, double const p_saturation_lower_bound = 0.00, double const p_saturation_upper_bound = 1.0);

    //Action Functions
    void enable_gesture(){ pros::c::optical_enable_gesture(m_port); }

    void disable_gesture(){ pros::c::optical_disable_gesture(m_port); }

    bool is_signature_1(){ return is_signature(m_signature_1); }

    bool is_signature_2(){ return is_signature(m_signature_2); }

    bool is_signature_3(){ return is_signature(m_signature_3); }
  };
}

#endif //OPTICAL_CLASS_H
