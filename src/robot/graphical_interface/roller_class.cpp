#include "robot/graphical_interface/roller_class.hpp"
#include "robot/graphical_interface/screen_class.hpp"


using namespace GUI;

Roller::Roller(short const p_xOrgin, short const p_yOrgin, short const p_length, std::vector<std::string>& p_roller_options,
  unsigned short p_state, lv_style_t& p_background_style ,lv_style_t& p_selected_style):
  m_roller_options(p_roller_options){
    m_xOrigin = p_xOrgin;
    m_yOrigin = p_yOrgin;
    m_length = p_length;
    m_state = p_state;
    m_background_style = &p_background_style;
    m_selected_style = &p_selected_style;
}

//Setter Function
void Roller::set_state(const unsigned short p_state){
  m_state = p_state;
  update_roller();
}

//Action Functions
void Roller::draw_roller(Screen& p_screen){
  std::string l_Roller{};

  for(int x = 0; x < m_roller_options.size()-1; x++){
    l_Roller += m_roller_options.at(x) + "\n";
  }
  l_Roller += m_roller_options.at(m_roller_options.size()-1);

  m_roller = lv_roller_create(p_screen.get_screen(), NULL);
  lv_roller_set_options(m_roller, l_Roller.c_str());

  lv_obj_align(m_roller, NULL, LV_ALIGN_IN_TOP_LEFT, m_xOrigin, m_yOrigin);
  lv_roller_set_hor_fit(m_roller, false);
  lv_obj_set_width(m_roller, m_length);
  lv_roller_set_visible_row_count(m_roller, 2);

  lv_roller_set_style(m_roller, LV_ROLLER_STYLE_BG, m_background_style);
  lv_roller_set_style(m_roller, LV_ROLLER_STYLE_SEL, m_selected_style);

  lv_roller_set_selected(m_roller, m_state, false);
}

void Roller::update_roller(){
  m_state = lv_roller_get_selected(m_roller);

  if(m_conected_int){
    *m_connected_int_pointer = m_connected_int_values->at(m_state);
  }
}

void Roller::add_connected_int(int& p_connected_int_pointer, std::vector<int>& p_connected_int_values){
  m_connected_int_pointer = &p_connected_int_pointer;
  m_connected_int_values = &p_connected_int_values;
  m_conected_int = true;
}
