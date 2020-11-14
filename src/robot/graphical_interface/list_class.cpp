#include "robot/graphical_interface/list_class.hpp"

List::List(){

}

/*
Important Functions:
lv_ddlist_set_selected() & lv_ddlist_get_selected & lv_ddlist_get_selected_str


*/

void List::draw_list(){
  m_list = lv_ddlist_create(lv_scr_act(), NULL);

  lv_ddlist_set_options(m_list, "Apple\n"
  "Banana\n"
  "Orange\n"
  "Melon\n"
  "Grape\n"
  "Raspberry");

  lv_obj_align(m_list, NULL, LV_ALIGN_IN_TOP_LEFT, m_xOrigin, m_yOrigin);
  lv_ddlist_set_fix_height(m_list, m_width);
  lv_ddlist_set_hor_fit(m_list, m_length);

  lv_ddlist_set_style(m_list, LV_DDLIST_STYLE_BG, m_background_style);
  lv_ddlist_set_style(m_list, LV_DDLIST_STYLE_SEL, m_selected_style);
  lv_ddlist_set_style(m_list, LV_DDLIST_STYLE_SB, m_scrollbar_style);
}

void List::update_list(){

}

void List::add_connected_int(int& p_connected_int_pointer, std::vector<int>& p_connected_int_values){
  m_connected_int_pointer = &p_connected_int_pointer;
  m_connected_int_values = &p_connected_int_values;
}
