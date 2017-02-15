#ifndef MY_DRAWABLE_
#define MY_DRAWABLE_

#include "point.hpp"

class MyDrawable {
public:
  virtual void draw() = 0;
  virtual int size() = 0;
  virtual void scale(float) = 0;
  virtual void rotate(float) = 0;
  virtual void translate(MyPoint *) = 0;
  virtual void setScale(float) = 0;
  virtual void setAngle(float) = 0;
  virtual void setPosition(MyPoint *) = 0;
  virtual void setAlpha(float) = 0;
  virtual void setColor(int) = 0;
  virtual void scaleColor(int, float) = 0;
  virtual void embedScale() = 0;
  virtual void embedAngle() = 0;
  virtual void embedPosition() = 0;
  virtual void limitDraw(float) = 0;
  virtual void useDrawLimit(bool) = 0;
  virtual MyPoint *getPosition() = 0;
};

#endif // ifndef MY_DRAWABLE_
