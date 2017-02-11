#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.hpp"


class Circle : public Shape{
 protected:
  float radius;
 public:
  Circle();
  Circle(float r,float x,float y);
  void SetRadius(float r);
  void Draw();
 
};


#endif

