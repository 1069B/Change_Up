#include "robot/robot_main.hpp"

#ifndef LABEL_CLASS_H
#define LABEL_CLASS_H

namespace GUI{

  enum LABEL_TYPE{
    INT_POINTER,
    DOUBLE_POINTER,
    BOOL_POINTER,
    STRING_POINTER,

    INT_FUNCTION,
    DOUBLE_FUNCTION,
    BOOL_FUNCTION,
    STRING_FUNCTION,

    DEFAULT
  };

  class Label{
  private:
    short m_xOrigin{};
    short m_yOrigin{};

    std::string m_text{};

    int* m_int_pointer;
    double* m_double_pointer;
    std::string* m_string_pointer;
    bool* m_bool_pointer;

    std::function<int()> m_int_function;
    std::function<double()> m_double_function;
    std::function<std::string()> m_string_function;
    std::function<bool()> m_bool_function;

    LABEL_TYPE m_lable_type;

    lv_obj_t* m_label{};
    lv_style_t* m_style{};

  public:
    /*  Constuctors  */
    Label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text);

    Label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, int& p_int_value);
    Label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, double& p_double_value);
    Label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::string& p_string_value);
    Label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, bool& p_bool_value);

    Label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<int()> p_int_value);
    Label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<double()> p_double_value);
    Label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<std::string()> p_string_value);
    Label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<bool()> p_bool_value);

    /*  Getting Function  */
    short get_xOrigin(){ return m_xOrigin; }

    short get_yOrigin(){ return m_yOrigin; }

    std::string get_text(){ return m_text; }

    lv_style_t* get_style(){ return m_style; }

    /*  Setter Function  */
    void set_xOrgin(short const p_xOrigin){ m_xOrigin = p_xOrigin; }

    void set_yOrgin(short const p_yOrigin){ m_yOrigin = p_yOrigin; }

    void set_text(std::string const p_text){ m_text = p_text; }

    void set_style(lv_style_t& p_style){ m_style = &p_style; }

    /*  Action Functions */
    void draw_label();// TODO: Add Screen& p_screen

    void update_label();// TODO: Add Screen& p_screen

    std::string format_text();
  };
}

#endif // LABEL_CLASS_H
