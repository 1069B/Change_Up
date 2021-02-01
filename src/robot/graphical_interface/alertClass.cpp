#include "robot/graphical_interface/alertClass.hpp"

Alert::Alert(){}

bool Alert::m_repeat = true;

void Alert::draw(std::string const p_message){
  m_alert = lv_mbox_create(lv_scr_act(), NULL);

  lv_mbox_set_text(m_alert, p_message.c_str());
  static const char * l_button[] ={"\221Resume Code", ""}; /*Button description. '\221' lv_button like control char*/
  lv_mbox_add_btns(m_alert, l_button, NULL);
  lv_obj_set_width(m_alert, 350);
  lv_obj_align(m_alert, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_mbox_set_action(m_alert, resume_program);
  m_repeat = true;
  while(m_repeat){
    pros::delay(5);
  }
  lv_mbox_start_auto_close(m_alert, 0);
}

lv_res_t Alert::resume_program(lv_obj_t* button_obj, const char *text){
  m_repeat = false;
  return LV_RES_OK;
}

Alert g_alert;
