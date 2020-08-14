#include "main.h"

#ifndef LABEL_CLASS_H
#define LABEL_CLASS_H

class Screen; // TODO: Remove Once we have decleration file

template <class T = std::string>
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
  Label<T>();

  /*  Getting Function  */
  short get_xOrgin(){ return m_xOrigin; }

  short get_yOrigin(){ return m_yOrigin; }

  std::string get_text(){ return m_text; }

  T get_dynamic_functionality(){ return m_dynamic_functionality; }

  lv_style_t* get_style(){ return m_style; }

  /*  Setter Function  */
  void set_xOrgin(short const p_xOrgin){ m_xOrigin = p_xOrgin; }

  void set_yOrgin(short const p_yOrgin){ m_yOrigin = p_yOrgin; }

  void set_text(std::string const p_text){ m_text = p_text; }

  void set_dynamic_functionality(T p_dynamic_functionality){ m_dynamic_functionality = p_dynamic_functionality; }

  void set_style(lv_style_t& p_style){ m_style = &p_style; }

  /*  Action Functions */
  void draw_label();// TODO: Add Screen& p_screen

  void update_label();// TODO: Add Screen& p_screen

  std::string format_text();

  /*  Converstion Functions pointer -> std::string */
  std::string evaluate_value(int* p_pointer){ return std::to_string(*p_pointer); }

  std::string evaluate_value(double* p_pointer){ return std::to_string(*p_pointer).substr(0, std::to_string(*p_pointer).find(".")+3); }

  std::string evaluate_value(std::string* p_pointer){ return *p_pointer; }

  std::string evaluate_value(bool* p_pointer);

  /*  Converstion Functions function -> std::string */
  std::string evaluate_value(std::function<int()> p_function){ return std::to_string(p_function()); }

  std::string evaluate_value(std::function<double()> p_function){ return std::to_string(p_function()).substr(0, std::to_string(p_function()).find(".")+3); }

  std::string evaluate_value(std::function<std::string()> p_function){ return p_function(); }

  std::string evaluate_value(std::function<bool()> p_function);

  /*  No Dynamic Feature */
  std::string evaluate_value(std::string p_pointer){ return "Error"; }
};

template class Label<int*>;
template class Label<double*>;
template class Label<std::string*>;
template class Label<bool*>;

template class Label<std::function<int()>>;
template class Label<std::function<double()>>;
template class Label<std::function<std::string()>>;
template class Label<std::function<bool()>>;

#endif // LABEL_CLASS_H
