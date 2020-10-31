#include "robot/devices/data_storage_class.hpp"

void Data_Storing::check_node(pugi::xml_node p_node, std::string const p_node_name){
    if(!p_node.child(p_node_name.c_str())){// Node does not exist
        p_node.append_child(p_node_name.c_str());
    }
}

pugi::xml_attribute Data_Storing::retreive_attribute(std::string const p_varible_name, std::string const p_varible_type){
    m_doc.load_file(m_address.c_str());
    pugi::xml_node l_node = m_doc.child(m_class_name.c_str()).child(m_instance_name.c_str());

    if(!l_node.child(p_varible_name.c_str())){
        pugi::xml_node temp = l_node.append_child(p_varible_name.c_str());
        temp.append_attribute(p_varible_type.c_str());
        return temp.attribute(p_varible_type.c_str());
    }
    else{
        pugi::xml_node temp = l_node.child(p_varible_name.c_str());
        return temp.attribute(p_varible_type.c_str());
    }
}

Data_Storing::Data_Storing(std::string const p_address, std::string const p_class_name, std::string const p_instance_name){
  m_address = "/usd/" + p_address;
  m_class_name = p_class_name;
  m_instance_name = p_instance_name;

  if(get_sd_card_connected()){
    m_doc.load_file(m_address.c_str());
    check_node(m_doc, m_class_name);// Checks to make sure that the class node exists
    check_node(m_doc.child(m_class_name.c_str()), m_instance_name.c_str());// Checks to make sure that the instance node exists
    m_doc.save_file(m_address.c_str());
  }
};

void Data_Storing::store_int(std::string const p_varible_name, int const p_value){
  if(get_sd_card_connected()){
    retreive_attribute(p_varible_name, "int").set_value(p_value);
    m_doc.save_file(m_address.c_str());
  }
}
void Data_Storing::store_double(std::string const p_varible_name, double const p_value){
  if(get_sd_card_connected()){
    retreive_attribute(p_varible_name, "double").set_value(p_value);
    m_doc.save_file(m_address.c_str());
  }
}
void Data_Storing::store_bool(std::string const p_varible_name, bool const p_value){
  if(get_sd_card_connected()){
    retreive_attribute(p_varible_name, "bool").set_value(p_value);
    m_doc.save_file(m_address.c_str());
  }
}
void Data_Storing::store_string(std::string const p_varible_name, std::string const p_value){
  if(get_sd_card_connected()){
    retreive_attribute(p_varible_name, "string").set_value(p_value.c_str());
    m_doc.save_file(m_address.c_str());
  }
}

int Data_Storing::read_int(std::string const p_varible_name){
  if(get_sd_card_connected())
    return retreive_attribute(p_varible_name, "int").as_int();
  return INT_MAX;
}
double Data_Storing::read_double(std::string const p_varible_name){
  if(get_sd_card_connected())
    return retreive_attribute(p_varible_name, "double").as_double();
  return INT_MAX;
}
bool Data_Storing::read_bool(std::string const p_varible_name){
  if(get_sd_card_connected())
    return retreive_attribute(p_varible_name, "bool").as_bool();
  return false;// NOTE: IF ISSUE WITH NO FILES CHECK THIS
}
std::string Data_Storing::read_string(std::string const p_varible_name){
  if(get_sd_card_connected())
    return retreive_attribute(p_varible_name, "string").as_string();
  return "SD Card Not Found";
}
