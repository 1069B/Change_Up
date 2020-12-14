#include "robot/robot_main.hpp"

#ifndef SCREEN_CLASS_H
#define SCREEN_CLASS_H

namespace GUI{
  class Screen{
  private:
    lv_obj_t* m_screen;
    lv_style_t* m_style;

    std::vector<Rectangle*> m_rectangle_vector;

    /* Labels */
      std::vector<Label<std::string>> m_label_string_vector;
      /* Pointers */
      std::vector<Label<int*>*> m_label_int_pointer_vector;
      std::vector<Label<double*>*> m_label_double_pointer_vector;
      std::vector<Label<std::string*>*> m_label_string_pointer_vector;
      std::vector<Label<bool*>*> m_label_bool_pointer_vector;
      /* Functions */
      std::vector<Label<std::function<int()>>*> m_label_int_function_vector;
      std::vector<Label<std::function<double()>>*> m_label_double_function_vector;
      std::vector<Label<std::function<std::string()>>*> m_label_string_function_list;
      std::vector<Label<std::function<bool()>>*> m_label_bool_function_vector;

    std::vector<List*> m_list_vector;
    std::vector<Bar*> m_bar_vector;
    std::vector<Button*> m_button_vector;
    std::vector<Switch*> m_switch_vector;

    std::string m_screen_name;
    std::string m_error_screen;

    /* Static Members */
    static std::vector<Screen*> m_screen_vector;

    static std::string m_current_screen_name;
    static std::string m_previous_screen_name;
    static std::string m_next_screen_name;

    static Screen* m_current_screen_pointer;// TODO:: Created Deafult Screen
    static Screen* m_next_screen_pointer;

    static Data_Storing m_settings;


  public:
    /* Constructor */
    Screen();

    /* Getter Functions */
    std::string get_screen_name(){return m_screen_name; }

    lv_obj_t* get_screen(){return m_screen; }

    /* Add Functions */
    Rectangle& add_rectanlge();


    template Label<>

    Label<std::string>& add_label_string();

    Label<int*>& add_lable_int_pointer();
    Label<double*>& add_lable_double_pointer();
    Label<std::string*>& add_lable_string_pointer();
    Label<bool*>& add_lable_bool_pointer();
    /* Functions */
    Label<std::function<int()>>& add_label_int_function();
    Label<std::function<double()>>& add_label_double_function();
    Label<std::function<std::string()>>& add_label_string_function_list();
    Label<std::function<bool()>>& add_label_bool_function();

    List& add_list();
    Bar& add_bar();
    Button& add_button();
    Switch& add_switch();

    /* Action */
    void draw_screen();

    void update_screen();

    void delete_screen();

    static void task();
  };
}

#endif // SCREEN_CLASS_H
