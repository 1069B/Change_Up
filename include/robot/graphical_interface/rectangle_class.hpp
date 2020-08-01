#include "main.h"

class Rectangle{
private:
  short m_xOrigin;
  short m_yOrigin;
  short m_length;
  short m_width;

  lv_style_t *m_style;
public:
  /*  Constuctors  */
  Rectangle();

  /*  Getting Function  */
  short get_xOrgin(){ return m_xOrigin; }

  short get_yOrigin(){ return m_yOrigin; }

  short get_length(){ return m_length; }

  short get_width(){ return m_width; }

  lv_style_t* get_style(){ return m_style; }

  /*  Setter Function  */
  void set_xOrgin(const short p_xOrgin);

  void set_yOrgin(const short p_yOrgin);

  void set_legnth(const short p_length);

  void set_width(const short p_width);

  void set_style(lv_style_t& p_style);
};
