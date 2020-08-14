#include "robot/graphical_interface/label_class.hpp"

/*  Constuctors  */
template <class T>
Label<T>::Label(){

}

/*  Action Function */
template <class T>
void Label<T>::draw_label(){
  m_label = lv_label_create(lv_scr_act(), NULL); // TODO: Change parent
  lv_obj_align(m_label, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, m_xOrigin, m_yOrigin);  // TODO: Change parent
  lv_label_set_text(m_label, format_text().c_str());
  lv_obj_set_style(m_label, m_style);
}

template <class T>
void Label<T>::update_label(){
  lv_label_set_text(m_label, format_text().c_str());
}

template <class T>
std::string Label<T>::format_text(){
  if(m_text.find("%d") != -1){// Dynamic
    return m_text.substr(0, m_text.find("%d")) + evaluate_value(m_dynamic_functionality) + m_text.substr(m_text.find("%d")+2);
  }
  else{// No dynamic
    return m_text;
  }
}

/*  Converstion Functions */
template <class T>
std::string Label<T>::evaluate_value(bool* p_pointer){
  if(*p_pointer == true)
    return "True";
  return "False";
}

template <class T>
std::string Label<T>::evaluate_value(std::function<bool()> p_function){
  if(p_function() == true)
    return "True";
  return "False";
}
