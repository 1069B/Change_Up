#include "main.h"

#ifndef BUTTON_CLASS_H
#define BUTTON_CLASS_H

template<class T = std::string>
class Button{
private:
   std::string name{};
   bool toggled{};
   bool pressed{};

public:
  //constructors

  Button<T>(std::string const p_name, bool const p_toggled, bool const p_pressed);

  //getter function

  std::string get_name(){ return m_name; }

  bool get_toggled(){ return m_toggled; }

  bool get_pressed(){return m_pressed; }

  //setter function
  void set_name(std::string const p_text){ m_text = p_text; }

  void set_toggled(bool const p_toggled){ m_toggled = p_toggled; }

  void set_pressed(bool const p_pressed){ m_}
}
