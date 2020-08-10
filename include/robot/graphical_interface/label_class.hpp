#include "main.h"

#ifndef LABEL_CLASS_H
#define LABEL_CLASS_H

class Screen; // TODO: Remove Once we have decleration file

template <class T>
class Label{
private:
  short m_xOrigin{};
  short m_yOrigin{};

  std::string m_text{};

  T m_dynamic_functionality;

  lv_obj_t* m_label{};
  lv_style_t* m_style{};

public:
  /*  Constuctors  */
  Label();

  /*  Getting Function  */
  short get_xOrgin(){ return m_xOrigin; }

  short get_yOrigin(){ return m_yOrigin; }

  std::string get_text(){ return m_text; }

  T get_dynamic_functionality(){ return m_dynamic_functionality; }

  lv_style_t* get_style(){ return m_style; }

  /*  Setter Function  */
  void set_xOrgin(short const p_xOrgin);

  void set_yOrgin(short const p_yOrgin);

  void set_text(short const p_text);

  void set_dynamic_functionality(T p_dynamic_functionality);

  void set_style(lv_style_t& p_style);

  /*  Action Function */
  void draw_label(Screen& p_screen);

  void update_label(Screen& p_screen);

  std::string format_text();
};

#endif // LABEL_CLASS_H
