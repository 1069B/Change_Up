#include "robot/graphical_interface/screen_class.hpp"
#include "robot/graphical_interface/rectangle_class.hpp"

using namespace GUI;
/* Constructor */
Screen::Screen(){

}

/* Add Functions */
GUI::Rectangle& Screen::add_rectanlge(std::string const p_name, short const p_xOrgin, short const p_yOrgin, short const p_length, short const p_width, lv_style_t& p_style){
  for(int x = 0; x < m_rectangle_vector.size(); x++){
    if(m_rectangle_vector.at(x)->get_name() == p_name)
      return *m_rectangle_vector.at(x);
  }

  Rectangle* l_new_rectangle{new Rectangle(p_name, p_xOrgin, p_yOrgin, p_length, p_width, p_style)};
  m_rectangle_vector.push_back(l_new_rectangle);
  return *l_new_rectangle;
}

template <typename T = std::string>
Label& Screen::add_label(std::string const p_name, short const p_xOrigin, short const p_yOrigin, lv_style_t& p_style, std::string const p_text){

}


List& Screen::add_list(){}
Bar& Screen::add_bar(){}
Button& Screen::add_button(){}
Switch& Screen::add_switch(){}

/* Action */
void Screen::draw_screen(){

}

void Screen::update_screen(){

}

void Screen::delete_screen(){

}

/* Static */
void Screen::task(){

}
