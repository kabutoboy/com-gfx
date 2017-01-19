#ifndef MY_DRAWABLE_
#define MY_DRAWABLE_

#include "point.hpp"

using namespace std;

class MyDrawable {
public:

  virtual void draw() {}

  virtual void scale(float)         = 0;
  virtual void rotate(float)        = 0;
  virtual void translate(MyPoint *) = 0;
};

#endif // ifndef MY_DRAWABLE_
