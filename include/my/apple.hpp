#ifndef MY_APPLE_
#define MY_APPLE_

#include "circle.hpp"
#include "flower.hpp"
#include "group.hpp"
#include "point.hpp"

class MyApple : public MyGroup {
public:
  static float constexpr RADIUS = 50;
  MyApple(float = 1, float = 0, MyPoint * = new MyPoint({0, 0}));

protected:
};

#endif // ifndef MY_APPLE_
