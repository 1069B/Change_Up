#include "robot/graphical_interface/screen_class.hpp"
#include "robot/graphical_interface/label_class.hpp"
#include "robot/graphical_interface/rectangle_class.hpp"
#include "robot/graphical_interface/roller_class.hpp"
#include "robot/graphical_interface/bar_class.hpp"
#include "robot/graphical_interface/button_class.hpp"
#include "robot/graphical_interface/switch_class.hpp"
#include "robot/devices/timer_class.hpp"
#include "robot/robot_class.hpp"

using namespace GUI;
/* Constructor */
Screen::Screen(const std::string p_name){
  m_screen_name = p_name;
}
Screen::Screen(const std::string p_name, std::function<bool()> p_function, std::string const p_screen_name, bool const p_inversed){
  m_screen_name = p_name;
  add_relationship(p_function, p_screen_name, p_inversed);
}

/* Getter Functions */
Screen& Screen::find_screen(std::string const p_screen_name){
  for(auto x : s_screen_vector){
    if(x->get_screen_name() == p_screen_name)
      return *x;
  }
  return s_home_screen;
}

/* Add Functions */
GUI::Rectangle& Screen::create_rectanlge(short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, lv_style_t& p_style){
  Rectangle* l_new_rectangle{new Rectangle(p_xOrigin, p_yOrigin, p_length, p_width, p_style)};
  m_rectangle_vector.push_back(l_new_rectangle);
  return *l_new_rectangle;
}

Label& Screen::create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, lv_label_align_t const p_alignment){
  Label* l_new_label{new Label(p_xOrigin, p_yOrigin, p_style, p_text, p_alignment)};
  m_label_vector.push_back(l_new_label);
  return *l_new_label;
}
Label& Screen::create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, int& p_int_value, lv_label_align_t const p_alignment){
  Label* l_new_label{new Label(p_xOrigin, p_yOrigin, p_style, p_text, p_int_value, p_alignment)};
  m_label_vector.push_back(l_new_label);
  return *l_new_label;
}
Label& Screen::create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, double& p_double_value, lv_label_align_t const p_alignment){
  Label* l_new_label{new Label(p_xOrigin, p_yOrigin, p_style, p_text, p_double_value, p_alignment)};
  m_label_vector.push_back(l_new_label);
  return *l_new_label;
}
Label& Screen::create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::string& p_string_value, lv_label_align_t const p_alignment){
  Label* l_new_label{new Label(p_xOrigin, p_yOrigin, p_style, p_text, p_string_value, p_alignment)};
  m_label_vector.push_back(l_new_label);
  return *l_new_label;
}
Label& Screen::create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, bool& p_string_value, lv_label_align_t const p_alignment){
  Label* l_new_label{new Label(p_xOrigin, p_yOrigin, p_style, p_text, p_string_value, p_alignment)};
  m_label_vector.push_back(l_new_label);
  return *l_new_label;
}

Label& Screen::create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<int()> p_int_value, lv_label_align_t const p_alignment){
  Label* l_new_label{new Label(p_xOrigin, p_yOrigin, p_style, p_text, p_int_value, p_alignment)};
  m_label_vector.push_back(l_new_label);
  return *l_new_label;
}
Label& Screen::create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<double()> p_double_value, lv_label_align_t const p_alignment){
  Label* l_new_label{new Label(p_xOrigin, p_yOrigin, p_style, p_text, p_double_value, p_alignment)};
  m_label_vector.push_back(l_new_label);
  return *l_new_label;
}
Label& Screen::create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<std::string()> p_string_value, lv_label_align_t const p_alignment){
  Label* l_new_label{new Label(p_xOrigin, p_yOrigin, p_style, p_text, p_string_value, p_alignment)};
  m_label_vector.push_back(l_new_label);
  return *l_new_label;
}
Label& Screen::create_label(short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text, std::function<bool()> p_bool_value, lv_label_align_t const p_alignment){
  Label* l_new_label{new Label(p_xOrigin, p_yOrigin, p_style, p_text, p_bool_value, p_alignment)};
  m_label_vector.push_back(l_new_label);
  return *l_new_label;
}

Roller& Screen::create_roller(short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, std::vector<std::string>& p_roller_options, unsigned short p_state, lv_style_t& p_background_style, lv_style_t& p_selected_style){
    Roller* l_new_roller{new Roller(p_xOrigin, p_yOrigin, p_length, p_width, p_roller_options, p_state, p_background_style, p_selected_style)};
    m_roller_vector.push_back(l_new_roller);
    return *l_new_roller;
  }

Bar& Screen::create_bar(short const p_xOrigin, short const p_yOrigin, short const p_length, short const p_width, int const p_position, int const p_range_minimum, int const p_range_maximum, lv_style_t&  p_bar_style, lv_style_t&  p_indicator_style){
  Bar* l_new_bar{new Bar(p_xOrigin, p_yOrigin, p_length, p_width, p_position, p_range_minimum, p_range_maximum, p_bar_style, p_indicator_style)};
  m_bar_vector.push_back(l_new_bar);
  return *l_new_bar;
}

Button& Screen::create_button(std::string const p_text, short const p_yOrigin, short const p_xOrigin, short const p_width, short const p_height, lv_style_t& p_style_pressed, lv_style_t& p_style_released){
  Button* l_new_button{new Button(p_text, p_yOrigin, p_xOrigin, p_width, p_height, p_style_pressed, p_style_released)};
  m_button_vector.push_back(l_new_button);
  return *l_new_button;
}

Switch& Screen::create_switch(short const p_xOrgin, short const p_yOrgin, int const p_state, lv_style_t& p_background_style, lv_style_t& p_indicator_style, lv_style_t& p_true_style, lv_style_t& p_false_style){
    Switch* l_new_switch{new Switch(p_xOrgin, p_yOrgin, p_state, p_background_style, p_indicator_style, p_true_style, p_false_style)};
    m_switch_vector.push_back(l_new_switch);
    return *l_new_switch;
  }

/* Action */
void Screen::draw_screen(){
  m_screen = lv_cont_create(lv_scr_act(), NULL);
  lv_obj_align(m_screen, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_obj_set_size(m_screen, 480, 240);
  lv_obj_set_style(m_screen, &GUI_STYLES::default_background);

  for(auto x : m_rectangle_vector)
    x->draw_rectangle(*this);

  for(auto x : m_label_vector)
    x->draw_label(*this);

  for(auto x : m_bar_vector)
    x->draw_bar(*this);

  for(auto x : m_button_vector)
    x->draw_button(*this);

  for(auto x : m_switch_vector)
    x->draw_switch(*this);

  for(auto x : m_roller_vector)
    x->draw_roller(*this);

  m_displayed = true;
}
void Screen::update_screen(){
  for(auto x : m_rectangle_vector)
    x->update_rectangle();

  for(auto x : m_label_vector)
    x->update_label();

  for(auto x : m_roller_vector)
    x->update_roller();

  for(auto x : m_bar_vector)
    x->update_bar();

  for(auto x : m_button_vector)
    x->update_button(*this);

  for(auto x : m_switch_vector)
    x->update_switch();
}
void Screen::delete_screen(){
  if(m_displayed){
    lv_obj_clean(m_screen);
    lv_obj_del(m_screen);
    m_displayed = false;
  }
}

void Screen::add_relationship(std::function<bool()> p_function, std::string const p_screen_name, bool const p_inversed){
  m_related_function = p_function;
  m_error_screen_name = p_screen_name;
  m_related_screen_inversed = p_inversed;
  m_screen_relation = true;
}

/* Static Members */
std::vector<Screen*> Screen::s_screen_vector{};

std::string Screen::s_current_screen_name{"Blank"};
std::string Screen::s_previous_screen_name{};
std::string Screen::s_next_screen_name{};

Screen& Screen::s_home_screen{ create_screen("Home") };
Screen& Screen::s_disconnected_screen{ create_screen("Disconnected") };

Screen* Screen::s_current_screen_pointer{ &s_home_screen };

Data_Storing Screen::s_settings{"Settings.xml", "GUI", "Main"};
Timer Screen::s_timer{};

Screen& Screen::create_screen(const std::string p_name){
  for(auto x : s_screen_vector){
    if(x->get_screen_name() == p_name)
      return *x;
  }

  Screen* l_new_screen{new Screen(p_name)};
  s_screen_vector.push_back(l_new_screen);
  return *l_new_screen;
};
Screen& Screen::create_screen(const std::string p_name, std::function<bool()> p_function, std::string const p_screen_name, bool const m_inversed){
  for(auto x : s_screen_vector){
    if(x->get_screen_name() == p_name)
      return *x;
  }

  Screen* l_new_screen{new Screen(p_name, p_function, p_screen_name, m_inversed)};
  s_screen_vector.push_back(l_new_screen);
  return *l_new_screen;
}


void Screen::initialize(Robot& p_robot){
  if(p_robot.get_recall_settings()){
    s_next_screen_name = s_settings.initialize_string("Current_Screen_Name", "Home");
  }
  else{
    s_next_screen_name = "Home";
  }
  s_timer.set_flag_delay(0);
}

void Screen::draw_current_screen(){
  s_current_screen_name = s_next_screen_name;
  s_current_screen_pointer = &find_screen(s_current_screen_name);
  s_settings.store_string("Current_Screen_Name", s_current_screen_name);

  if(s_current_screen_pointer->m_screen_relation){// If there is a screen relation
    if(s_current_screen_pointer->m_related_function() && !s_current_screen_pointer->m_related_screen_inversed){
      s_current_screen_name = s_current_screen_pointer->m_error_screen_name;
      s_current_screen_pointer = &find_screen(s_current_screen_name);
    }
    else if(!s_current_screen_pointer->m_related_function() && s_current_screen_pointer->m_related_screen_inversed){
      s_current_screen_name = s_current_screen_pointer->m_error_screen_name;
      s_current_screen_pointer = &find_screen(s_current_screen_name);
    }
    s_next_screen_name = s_current_screen_name;
  }

  s_current_screen_pointer->draw_screen();
}

void Screen::task(){
  if(s_current_screen_name != s_next_screen_name && s_timer.get_preform_action()){
    s_current_screen_pointer->delete_screen();
    s_previous_screen_name = s_current_screen_name;

    draw_current_screen();
  }
  s_current_screen_pointer->update_screen();
}
