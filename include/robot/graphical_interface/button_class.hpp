#include "main.h"

#ifndef BUTTON_CLASS_H
//#define BUTTON_CLASS_H

template<class T = std::string>
class Button{
private:
   std::string m_name{};
   bool m_toggled{};
   bool m_pressed{};
   bool m_active{};
   short m_xOrigin{};
   short m_yOrigin{};
   short m_width{};
   short m_height{};
   lv_obj_t*m_style_pressed{};
   lv_obj_t*m_style_released{};
   lv_obj_t*m_style_inactive{};


public:
  //constructors

  Button<T>(std::string const p_name, bool const p_toggled, bool const p_pressed, bool const p_active, short const p_yOrigin, short const p_xOrigin, short const p_width, short const p_height, lv_style_t& p_style_pressed, lv_style_t& p_style_released, lv_style_t& p_style_inactive);

  //getter function

  std::string get_name(){ return m_name; }

  bool get_toggled(){ return m_toggled; }

  bool get_pressed(){ return m_pressed; }

  bool get_active(){ return m_active; }

  short get_xOrigin(){ return m_xOrigin; }

  short get_YOrigin(){ return m_yOrigin; }

  short get_width(){ return m_width; }

  short get_height(){ return m_height; }

  lv_style_t* get_style_pressed(){ return m_style_pressed; }

  lv_style_t* get_style_released(){ return m_style_released; }

  lv_style_t* get_style_inactive(){ return m_style_inactive; }

  //setter function
  void set_name(std::string const p_text){ m_text = p_text; }

  void set_toggled(bool const p_toggled){ m_toggled = p_toggled; }

  void set_pressed(bool const p_pressed){ m_pressed = p_pressed; }

  void set_active(bool const p_active){ m_active = p_active; }

  void set_xOrigin(short const p_xOrigin){ m_xOrigin = p_xOrigin; }

  void set_yOrigin(short const p_yOrigin){ m_yOrigin = p_yOrigin; }

  void set_height(short const p_height){ m_height = p_height; }

  void set_width(short const p_width){ m_width = p_width; }

  void set_style_pressed(lv_style_t& p_style_pressed){ m_style_pressed = &p_style_pressed; }

  void set_style_released(lv_style_t& p_style_released){ m_style_released = &p_style_released; }

  void set_style_inactive(lv_style_t& p_style_inactive){ m_style_inactive = &p_style_inactive}

  // Action Functions
  void draw

  #endif //BUTTON_CLASS_H
