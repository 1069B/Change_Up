#include "main.h"

#ifndef ALERTCLASS_H
#define ALERTCLASS_H

class Alert{
private:
  lv_obj_t* m_alert;
  static bool m_repeat;

public:
  Alert();

  void draw(std::string const p_message);

  static lv_res_t resume_program(lv_obj_t* button_obj, const char *text);
};

extern Alert g_alert;

#endif // ALERTCLASS_H
