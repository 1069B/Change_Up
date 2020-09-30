#include "main.h"

#ifndef FILE_H
#define FILE_H

/*
Frequent Long Information (Writing & Appending)
  Hold all of the changes and write to file all at once

Infrequent Short Information (Reading & Writting & Appending)
  Motor1_port=2
  Motor2_port_9

*/

// read

// write (Entire File at once)

// append

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

  /*  Action  */
  void add_line(std::string const p_text);

  void write_buffer();

  void clear_buffer();



};

#endif // FILE_H
