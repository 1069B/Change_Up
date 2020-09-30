#include "robot/devices/file_class.hpp"

Data_Logging::Data_Logging(std::string const p_address){
  m_address = "/usd/" + p_address;
};

void Data_Logging::add_line(std::string const p_text){
  m_buffer += p_text + "\n";
}

void Data_Logging::write_buffer(){
  if(get_sd_card_connected()){
    m_file.open(m_address, std::ios::out);
    m_file << m_buffer << std::endl;
    m_file.close();
  }
}

void Data_Logging::clear_buffer(){
  m_buffer = "";
}
