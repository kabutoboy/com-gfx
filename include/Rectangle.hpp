#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.hpp"


class Rectangle : public Shape{
 protected:
  float size;
 public:
  Rectangle();
  Rectangle(float s);
  void Draw();
  void SetSize(float s);
};

#endif
