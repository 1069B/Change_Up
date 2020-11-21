#include "robot/robot_main.hpp"
#include "pugi/pugiconfig.hpp"
#include "pugi/pugixml.hpp"

#ifndef DATALOGGING_H
#define DATALOGGING_H

class Data_Storing{
private:
  std::string m_address{};
  pugi::xml_document m_doc;

  std::string m_class_name{};
  std::string m_instance_name{};

  /* Internal Functions */
  void check_node(pugi::xml_node p_node, std::string const p_node_name);

  pugi::xml_attribute retreive_attribute(std::string const p_varible_name, std::string const p_varible_type);

  bool check_attribute(std::string const p_varible_name, std::string const p_varible_type);
public:
  /*  Constructors  */
  Data_Storing(std::string const p_address, std::string const p_class_name, std::string const p_instance_name);

  /*  Getter Functions  */
  std::string get_address(){ return m_address; };

  std::string get_class_name(){ return m_class_name; };

  std::string get_instance_name(){ return m_instance_name; };

  static bool get_sd_card_connected(){ return pros::c::usd_is_installed(); };

  /*  File Write Functions  */
  void store_int(std::string const p_varible_name, int const p_value);

  void store_double(std::string const p_varible_name, double const p_value);

  void store_bool(std::string const p_varible_name, bool const p_value);

  void store_string(std::string const p_varible_name, std::string const p_value);

  /*  File Read Fucntions  */
  int read_int(std::string const p_varible_name);

  double read_double(std::string const p_varible_name);

  bool read_bool(std::string const p_varible_name);

  std::string read_string(std::string const p_varible_name);

  /* Varible Intitialize Functions*/
  int intitialize_int(std::string const p_varible_name, int const p_value);

  double intitialize_double(std::string const p_varible_name, double const p_value);

  bool intitialize_bool(std::string const p_varible_name, bool const p_value);

  std::string intitialize_string(std::string const p_varible_name, std::string const p_value);

};

#endif // DATALOGGING_H
