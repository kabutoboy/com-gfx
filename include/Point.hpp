#ifndef POINT_H
#define  POINT_H

#include "Shape.hpp"

class Point : public Shape{
 protected:
  float x0,y0;
 public:
  Point();
  Point(float x,float y);
  void SetPosition(float x,float y);
  void Draw();

};

#endif
