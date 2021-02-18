#include "robot/robot_main.hpp"

bool outside_range(double const p_value, double const p_range){
  if(fabs(p_range) < fabs(p_value))
    return true;
  return false;  
}