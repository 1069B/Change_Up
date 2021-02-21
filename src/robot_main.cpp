#include "robot/robot_main.hpp"

bool outside_range(double const p_value, double const p_range){
  if(fabs(p_range) < fabs(p_value))
    return true;
  return false;  
}

bool inside_range(double const p_value, double const p_lower_bound, double const p_upper_bound){
  if(p_lower_bound < p_value && p_value < p_upper_bound)
    return true;
  return false;
}