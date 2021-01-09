#include "robot/graphical_interface/list_class.hpp"

using namespace GUI;

List::List(std::string const p_name,short const p_xOrgin, short const p_yOrgin, short const p_length, short const p_width, std::vector<std::string>& p_list_options,
  unsigned short p_state, lv_style_t* p_background_style ,lv_style_t* p_selected_style, lv_style_t* p_scrollbar_style):
  m_list_options(p_list_options){
    m_name = p_name;
    m_xOrigin = p_xOrgin;
    m_yOrigin = p_yOrgin;
    m_length = p_length;
    m_width = p_width;
    m_state = p_state;
    m_background_style = p_background_style;
    m_selected_style = p_selected_style;
    m_scrollbar_style = p_scrollbar_style;
}

void List::set_state(const unsigned short p_state){
  m_state = p_state;
  lv_ddlist_set_selected(m_list, m_state);
  update_list();
}

void List::draw_list(){
  std::string l_list{};

  for(std::string& x : m_list_options){
    l_list += x + "\n";
  }

  m_list = lv_ddlist_create(lv_scr_act(), NULL);
  lv_ddlist_set_options(m_list, l_list.c_str());

  lv_obj_align(m_list, NULL, LV_ALIGN_IN_TOP_LEFT, m_xOrigin, m_yOrigin);
  lv_ddlist_set_fix_height(m_list, m_width);
  lv_ddlist_set_hor_fit(m_list, m_length);

  lv_ddlist_set_style(m_list, LV_DDLIST_STYLE_BG, m_background_style);
  lv_ddlist_set_style(m_list, LV_DDLIST_STYLE_SEL, m_selected_style);
  lv_ddlist_set_style(m_list, LV_DDLIST_STYLE_SB, m_scrollbar_style);

  lv_ddlist_set_selected(m_list, m_state);
}

void List::update_list(){
  m_state = lv_ddlist_get_selected(m_list);

  if(m_conected_int){
    *m_connected_int_pointer = m_connected_int_values->at(m_state);
  }
}

void List::add_connected_int(int& p_connected_int_pointer, std::vector<int>& p_connected_int_values){
  m_connected_int_pointer = &p_connected_int_pointer;
  m_connected_int_values = &p_connected_int_values;
  m_conected_int = true;
}
