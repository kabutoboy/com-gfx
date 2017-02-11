#ifndef SHAPE_H
#define SHAPE_H

#include "Color.hpp"


// --------------- Abstract class ----------

class Shape{ 
 protected:
  float x0;
  float y0;
 public:
  void SetPosition(float x,float y);
  void SetColor(double r,double g,double b);
  void SetColor(Color color);
  void Translate(float x,float y ,float z);
  void Rotate(float angle);
  void Scale(float sx,float sy);

  virtual void Draw() = 0;


};

#endif
