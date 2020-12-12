#include "robot/robot_main.hpp"

#ifndef SCREEN_CLASS_H
#define SCREEN_CLASS_H

namespace GUI{
  class Screen{
  private:
    short m_xOrgin;
    short m_yOrgin;
    short m_length;
    short m_width;

    lv_obj_t* m_container;
    lv_style_t* m_style;

    std::vector<Rectangle*> m_rectangle_list;

    /* Labels */
      std::vector<Label<std::string>> m_label_string_list;
      /* Pointers */
      std::vector<Label<int*>*> m_label_int_pointer_list;
      std::vector<Label<double*>*> m_label_double_pointer_list;
      std::vector<Label<std::string*>*> m_label_string_pointer_list;
      std::vector<Label<bool*>*> m_label_bool_pointer_list;
      /* Functions */
      std::vector<Label<std::function<int()>>*> m_label_int_function_list;
      std::vector<Label<std::function<double()>>*> m_label_double_function_list;
      std::vector<Label<std::function<std::string()>>*> m_label_string_function_list;
      std::vector<Label<std::function<bool()>>*> m_label_bool_function_list;

    std::vector<List*> m_list_list;

    std::vector<Bar*> m_bar_list;





    std::string m_pageID;
    std::string m_relatedScreen;
    std::string& m_nextScreenID;




    std::vector<Button*> m_btnArray;
    std::vector<Label*> m_labelArray;
    std::vector<Meter*> m_meterArray;
    std::vector<Line*> m_lineArray;
    std::vector<Toggle*> m_toggleArray;
    std::vector<Rectangle*> m_rectArray;
  public:
    std::vector<Screen*> m_screenArray;
  int m_noVersion = 0;// For screens with only one version
  std::string m_previousScreenID = "A";
  std::string m_currentScreenID = "B";
  std::string m_nextScreenID = "C";
  Screen* m_nextScreen;// = new Screen("Blank", noVersion, defaultBackground, nextScreenID);
  Screen* m_currentScreen;// = new Screen("Blank", noVersion, defaultBackground, nextScreenID);
  Timer m_timer;
  ExternalFile m_GUIStorage;
  void updateScreen();

public:
  GraphicalInterface(const std::string p_startingScreen="Home");

  void addScreen(const std::string p_name, lv_style_t& p_style = defaultBackground);
  void addScreen(const std::string p_name, const int p_xOrgin, const int p_yOrgin, const int p_length, const int p_width, lv_style_t& p_style = defaultBackground);

  };
}

#endif // SCREEN_CLASS_H
