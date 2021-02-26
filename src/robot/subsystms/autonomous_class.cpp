#include "robot/robot_class.hpp"

#include "robot/devices/motor_class.hpp"
#include "robot/devices/timer_class.hpp"

#include "robot/graphical_interface/screen_class.hpp"
#include "robot/graphical_interface/button_class.hpp"

#include "robot/subsystems/holonomic_class.hpp"
#include "robot/subsystems/manipulator.hpp"
#include "robot/subsystems/autonomous_class.hpp"
#include "robot/subsystems/autonomous_rountines_class.hpp"

Autonomous::Autonomous(Robot& p_robot):
m_robot(p_robot){}

void Autonomous::set_selected_routine(std::string p_routine_name){
    for(auto x : m_routines){
        if(x->get_name() == p_routine_name)
        m_selected_routine = x;
    }
}

Autonomous_Routine& Autonomous::add_autonomous_routine(std::string p_routine_name, Robot_Alliance p_routine_alliance){
  for(auto x : m_routines){
    if(x->get_name() == p_routine_name)
      return *x;
  }

  Autonomous_Routine* l_new_routine{new Autonomous_Routine(*this, p_routine_name, p_routine_alliance)};
  m_routines.push_back(l_new_routine);
  return *l_new_routine;
}

bool Autonomous::is_running(){
    if(m_selected_routine == NULL)
        return false;

    return m_selected_routine->m_running_autonomous; 
}

void Autonomous::task(){
    if(m_selected_routine == NULL)
        return;
    m_selected_routine->task();   
}

void Autonomous::start_autonomous(){
    if(m_selected_routine == NULL)
        return;
    m_selected_routine->start_autonomous();
}

void Autonomous::end_autonomous(){
    if(m_selected_routine == NULL)
        return;
    m_selected_routine->end_autonomous();
}

int Autonomous::set_selected_routine_GUI(){
    switch ((int)m_gui_selected_program){
        case 11: // Red Program 1: Red_Corner_and_Center
            m_robot.set_robot_alliance(ROBOT_RED);
            m_robot.get_autonomous().set_selected_routine("Red_Corner_and_Center");
            break;

        case 12: // Red Program 2
            m_robot.set_robot_alliance(ROBOT_RED);
            m_robot.get_autonomous().set_selected_routine("Skills");
            break;
        
        case 13: // Red Program 3
            m_robot.set_robot_alliance(ROBOT_RED);
            m_robot.get_autonomous().set_selected_routine("Skills");
            break;

        case 14: // Red Program 4
            m_robot.set_robot_alliance(ROBOT_RED);
            m_robot.get_autonomous().set_selected_routine("Skills");
            break;

        case 21: // Blue Program 1
            m_robot.set_robot_alliance(ROBOT_BLUE);
            m_robot.get_autonomous().set_selected_routine("Skills");
            break;

        case 22: // Blue Program 2
            m_robot.set_robot_alliance(ROBOT_BLUE);
            m_robot.get_autonomous().set_selected_routine("Skills");
            break;
        
        case 23: // Blue Program 3
            m_robot.set_robot_alliance(ROBOT_BLUE);
            m_robot.get_autonomous().set_selected_routine("Skills");
            break;

        case 24: // Blue Program 4
            m_robot.set_robot_alliance(ROBOT_BLUE);
            m_robot.get_autonomous().set_selected_routine("Skills");
            break;

        default:// Skills
            m_robot.set_robot_alliance(ROBOT_SKILLS);
            m_robot.get_autonomous().set_selected_routine("Skills");
            break;
    }
    return 0;
}

void Autonomous::define_GUI(){
    GUI::Screen &team_selector = GUI::Screen::create_screen("Team Selector");
    team_selector.create_rectangle(0, 0, 480, 40, GUI_STYLES::white_text);
    team_selector.create_label(0, 10, GUI_STYLES::red_text, "Team Selector", LV_ALIGN_IN_TOP_MID);
	GUI::Button &red_team = team_selector.create_button("Red Alliance", 10, 100, 225, 40, GUI_STYLES::red_button_released, GUI_STYLES::red_button_pressed);
	red_team.add_connected_screen("Red Autonomous Programs");
	GUI::Button &blue_team = team_selector.create_button("Blue Alliance", 245, 100, 225, 40, GUI_STYLES::blue_button_released, GUI_STYLES::blue_button_pressed);
	blue_team.add_connected_screen("Blue Autonomous Programs");
	GUI::Button &skills_team = team_selector.create_button("Skills", 125, 160, 225, 40, GUI_STYLES::green_button_released, GUI_STYLES::green_button_pressed);
	skills_team.add_connected_screen("Home");
    skills_team.add_connected_double(31, m_gui_selected_program);
    skills_team.add_connected_function(std::bind(&Autonomous::set_selected_routine_GUI, *this));

    /* Red Programs */
    GUI::Screen &red_alliance = GUI::Screen::create_screen("Red Autonomous Programs");
    red_alliance.create_rectangle(0, 0, 480, 40, GUI_STYLES::white_text);
    red_alliance.create_label(0, 10, GUI_STYLES::red_text, "Red Autonomous Programs", LV_ALIGN_IN_TOP_MID);
	GUI::Button &red_program_1 = red_alliance.create_button("Red Corner and Center", 10, 100, 225, 40, GUI_STYLES::red_button_released, GUI_STYLES::red_button_pressed);
	red_program_1.add_connected_screen("Home");
    red_program_1.add_connected_double(11, m_gui_selected_program);
    red_program_1.add_connected_function(std::bind(&Autonomous::set_selected_routine_GUI, *this));
	GUI::Button &red_program_2 = red_alliance.create_button("Red Program 2", 245, 100, 225, 40, GUI_STYLES::red_button_released, GUI_STYLES::red_button_pressed);
	red_program_2.add_connected_screen("Home");
    red_program_2.add_connected_double(12, m_gui_selected_program);
    red_program_2.add_connected_function(std::bind(&Autonomous::set_selected_routine_GUI, *this));
	GUI::Button &red_program_3 = red_alliance.create_button("Red Program 3", 10, 180, 225, 40, GUI_STYLES::red_button_released, GUI_STYLES::red_button_pressed);
	red_program_3.add_connected_screen("Home");
    red_program_3.add_connected_double(13, m_gui_selected_program);
    red_program_3.add_connected_function(std::bind(&Autonomous::set_selected_routine_GUI, *this));
    GUI::Button &red_program_4 = red_alliance.create_button("Red Program 4", 245, 180, 225, 40, GUI_STYLES::red_button_released, GUI_STYLES::red_button_pressed);
	red_program_4.add_connected_screen("Home");
    red_program_4.add_connected_double(14, m_gui_selected_program);
    red_program_4.add_connected_function(std::bind(&Autonomous::set_selected_routine_GUI, *this));

    /* Blue Programs */
    GUI::Screen &blue_alliance = GUI::Screen::create_screen("Blue Autonomous Programs");
    blue_alliance.create_rectangle(0, 0, 480, 40, GUI_STYLES::white_text);
    blue_alliance.create_label(0, 10, GUI_STYLES::blue_text, "Blue Autonomous Programs", LV_ALIGN_IN_TOP_MID);
	GUI::Button &blue_program_1 = blue_alliance.create_button("Blue Program 1", 10, 100, 225, 40, GUI_STYLES::blue_button_released, GUI_STYLES::blue_button_pressed);
	blue_program_1.add_connected_screen("Home");
    blue_program_1.add_connected_double(21, m_gui_selected_program);
    blue_program_1.add_connected_function(std::bind(&Autonomous::set_selected_routine_GUI, *this));
	GUI::Button &blue_program_2 = blue_alliance.create_button("Blue Program 2", 245, 100, 225, 40, GUI_STYLES::blue_button_released, GUI_STYLES::blue_button_pressed);
	blue_program_2.add_connected_screen("Home");
    blue_program_2.add_connected_double(22, m_gui_selected_program);
    blue_program_2.add_connected_function(std::bind(&Autonomous::set_selected_routine_GUI, *this));
	GUI::Button &blue_program_3 = blue_alliance.create_button("Blue Program 3", 10, 180, 225, 40, GUI_STYLES::blue_button_released, GUI_STYLES::blue_button_pressed);
	blue_program_3.add_connected_screen("Home");
    blue_program_3.add_connected_double(23, m_gui_selected_program);
    blue_program_3.add_connected_function(std::bind(&Autonomous::set_selected_routine_GUI, *this));
    GUI::Button &blue_program_4 = blue_alliance.create_button("Blue Program 4", 245, 180, 225, 40, GUI_STYLES::blue_button_released, GUI_STYLES::blue_button_pressed);
	blue_program_4.add_connected_screen("Home");
    blue_program_4.add_connected_double(24, m_gui_selected_program);
    blue_program_4.add_connected_function(std::bind(&Autonomous::set_selected_routine_GUI, *this));
}