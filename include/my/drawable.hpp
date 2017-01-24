#ifndef MY_DRAWABLE_
#define MY_DRAWABLE_

#include "point.hpp"

class MyDrawable {
public:
  virtual void draw(float = 1) = 0;

  virtual void scale(float) = 0;
  virtual void rotate(float) = 0;
  virtual void translate(MyPoint *) = 0;
  virtual void setScale(float) = 0;
  virtual void setAngle(float) = 0;
  virtual void setPosition(MyPoint *) = 0;
  virtual void embedScale() = 0;
  virtual void embedAngle() = 0;
  virtual void embedPosition() = 0;
};

#endif // ifndef MY_DRAWABLE_
