#include "robot/robot_main.hpp"

#ifndef VISION_CLASS_H
#define VISION_CLASS_H

namespace SENSOR{
  class Vision_Signature{
  private:

  public:
    Vision_Signature();

    /* Getter Functions */
    double get_hight();

    double get_width();

    double get_area();

    double get_x_position();

    double get_y_position();

    /* Setter Functions */
    void set_signature();
  };
  
  class Vision{
  private:
    Robot& m_robot;

    std::string m_name;
    short m_port{};

    Vision_Signature m_signature_1;
    

    Data_Storing& m_settings;

  public:
    //Constructor
    Vision(Robot &p_robot, std::string const p_name, short const p_port);

    //Getter Functions
    short get_port(){ return m_port; }

    std::string get_name(){ return m_name; }

    Vision_Signature& get_signature_1(){ return m_signature_1; }

    /* Setter Functions */
    void set_port(short const p_port);


    /* Action Functions */
  };
}

#endif //VISION_CLASS_H
