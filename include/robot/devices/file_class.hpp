#include "main.h"

#ifndef FILE_H
#define FILE_H

class Data_Logging{
private:
  std::fstream m_file{};
  std::string m_address{};

  std::string m_buffer{};

public:
  /*  Constructors  */
  Data_Logging(std::string const p_address);

  /*  Getter  */
  std::fstream& get_file(){ return m_file; };

  std::string get_address(){ return m_address; };

  static bool get_sd_card_connected(){ return pros::c::usd_is_installed(); };

  /*  Setter  */
  void set_address(std::string const p_address){ m_address = p_address; };

  void set_buffer(std::string const p_buffer){ m_address = p_buffer; };

  /*  Action  */
  void add_line(std::string const p_text);

  void write_buffer();

  void clear_buffer();

  friend Data_Logging& operator<< (Data_Logging& out, std::string const p_input);
  friend Data_Logging& operator<< (Data_Logging& out, int const p_input);
  friend Data_Logging& operator<< (Data_Logging& out, double const p_input);
};

Data_Logging& operator<< (Data_Logging& out, std::string const p_input);
Data_Logging& operator<< (Data_Logging& out, int const p_input);
Data_Logging& operator<< (Data_Logging& out, double const p_input);

#endif // FILE_H
