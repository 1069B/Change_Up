#include "main.h"

#ifndef DATALOGGING_H
#define DATALOGGING_H

class Data_Storing{
private:
  pugi::xml_documentm_doc{};
  std::string m_address{};

public:
  /*  Constructors  */
  Data_Storing(std::string const p_address);

  /*  Getter  */
  std::fstream& get_file(){ return m_file; };

  std::string get_address(){ return m_address; };

  static bool get_sd_card_connected(){ return pros::c::usd_is_installed(); };

  /*  Setter  */

  /*  Action  */
};

#endif // DATALOGGING_H
