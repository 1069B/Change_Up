#include "robot/graphical_interface/label_class.hpp"
#include "robot/graphical_interface/screen_class.hpp"

using namespace GUI;

/*  Constuctors  */
Label::Label(std::string const p_name, short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text){
  m_name = p_name;
  m_xOrigin = p_xOrigin;
  m_yOrigin = p_yOrigin;
  m_style = &p_style;
  m_text = p_text;
  m_lable_type = DEFAULT;
}

Label::Label(std::string const p_name, short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, int& p_int_value){
  Label(p_name, p_xOrigin, p_yOrigin, p_style, p_text);
  m_int_pointer = &p_int_value;
  m_lable_type = INT_POINTER;
}
Label::Label(std::string const p_name, short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, double& p_double_value){
  Label(p_name, p_xOrigin, p_yOrigin, p_style, p_text);
  m_double_pointer = &p_double_value;
  m_lable_type = DOUBLE_POINTER;
}
Label::Label(std::string const p_name, short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::string& p_string_value){
  Label(p_name, p_xOrigin, p_yOrigin, p_style, p_text);
  m_string_pointer = &p_string_value;
  m_lable_type = STRING_POINTER;
}
Label::Label(std::string const p_name, short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, bool& p_bool_value){
  Label(p_name, p_xOrigin, p_yOrigin, p_style, p_text);
  m_bool_pointer = &p_bool_value;
  m_lable_type = BOOL_POINTER;
}

Label::Label(std::string const p_name, short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<int()> p_int_value){
  Label(p_name, p_xOrigin, p_yOrigin, p_style, p_text);
  m_int_function = p_int_value;
  m_lable_type = INT_FUNCTION;
}
Label::Label(std::string const p_name, short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<double()> p_double_value){
  Label(p_name, p_xOrigin, p_yOrigin, p_style, p_text);
  m_double_function = p_double_value;
  m_lable_type = DOUBLE_FUNCTION;
}
Label::Label(std::string const p_name, short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<std::string()> p_string_value){
  Label(p_name, p_xOrigin, p_yOrigin, p_style, p_text);
  m_string_function = p_string_value;
  m_lable_type = STRING_FUNCTION;
}
Label::Label(std::string const p_name, short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<bool()> p_bool_value){
  Label(p_name, p_xOrigin, p_yOrigin, p_style, p_text);
  m_bool_function = p_bool_value;
  m_lable_type = BOOL_FUNCTION;
}

/*  Action Function */
void Label::draw_label(Screen& p_screen){
  m_label = lv_label_create(p_screen.get_screen(), NULL);
  lv_obj_align(m_label, p_screen.get_screen(), LV_ALIGN_IN_TOP_LEFT, m_xOrigin, m_yOrigin);
  lv_label_set_text(m_label, format_text().c_str());
  lv_obj_set_style(m_label, m_style);
}

void Label::update_label(){
  lv_label_set_text(m_label, format_text().c_str());
}

std::string Label::format_text(){
  switch((int)m_lable_type) {
    case INT_POINTER:
      if(m_text.find("%d") != -1)
        return m_text.substr(0, m_text.find("%d")) + std::to_string(*m_int_pointer) + m_text.substr(m_text.find("%d")+2);

    case DOUBLE_POINTER:
      if(m_text.find("%d") != -1)
        return m_text.substr(0, m_text.find("%d")) + std::to_string(*m_double_pointer) + m_text.substr(m_text.find("%d")+2);

    case STRING_POINTER:
      if(m_text.find("%d") != -1)
        return m_text.substr(0, m_text.find("%d")) + *m_string_pointer + m_text.substr(m_text.find("%d")+2);

    case BOOL_POINTER:
      if(m_text.find("%d") != -1){
        if(*m_bool_pointer)
          return m_text.substr(0, m_text.find("%d")) + "True" + m_text.substr(m_text.find("%d")+2);
        else
          return m_text.substr(0, m_text.find("%d")) + "False" + m_text.substr(m_text.find("%d")+2);
      }

    case INT_FUNCTION:
      if(m_text.find("%d") != -1)
        return m_text.substr(0, m_text.find("%d")) + std::to_string(m_int_function()) + m_text.substr(m_text.find("%d")+2);

    case DOUBLE_FUNCTION:
      if(m_text.find("%d") != -1)
        return m_text.substr(0, m_text.find("%d")) + std::to_string(m_double_function()) + m_text.substr(m_text.find("%d")+2);

    case STRING_FUNCTION:
      if(m_text.find("%d") != -1)
        return m_text.substr(0, m_text.find("%d")) + m_string_function() + m_text.substr(m_text.find("%d")+2);

    case BOOL_FUNCTION:
      if(m_text.find("%d") != -1){
        if(m_bool_function())
          return m_text.substr(0, m_text.find("%d")) + "True" + m_text.substr(m_text.find("%d")+2);
        else
          return m_text.substr(0, m_text.find("%d")) + "False" + m_text.substr(m_text.find("%d")+2);
      }


    default:
      return m_text;
  }
}
