#ifndef MY_MAN_
#define MY_MAN_

#include "circle.hpp"
#include "group.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "sunflower.hpp"

class MyMan : public MyGroup {
public:
  static float constexpr HEAD_RADIUS = 20;
  static float constexpr BODY_THICKNESS = 40;
  static float constexpr BODY_LENGTH = 80;
  static float constexpr ARM_THICKNESS = 15;
  static float constexpr ARM_LENGTH = 80;
  static float constexpr LEG_THICKNESS = 20;
  static float constexpr LEG_LENGTH = 100;
  MyMan(float = 1, float = 0, MyPoint * = new MyPoint({0, 0}));
  MyGroup *head;
  MyGroup *body;
  MyGroup *arm11;
  MyGroup *arm12;
  MyGroup *arm21;
  MyGroup *arm22;
  MyGroup *leg11;
  MyGroup *leg12;
  MyGroup *leg21;
  MyGroup *leg22;

protected:
};

#endif // ifndef MY_MAN_
