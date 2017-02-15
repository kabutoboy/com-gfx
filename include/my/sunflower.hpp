#ifndef MY_SUNFLOWER_
#define MY_SUNFLOWER_

#include "circle.hpp"
#include "flower.hpp"
#include "group.hpp"
#include "point.hpp"

class MySunFlower : public MyGroup {
public:
  static float constexpr NUMBER_OF_PETALS = 8;
  static float constexpr RADIUS = 100;
  static float constexpr INNER_SEEDS_RADIUS = 30;
  static float constexpr OUTER_SEEDS_RADIUS = 40;
  MySunFlower(float = 1, float = 0, MyPoint * = new MyPoint({0, 0}));

protected:
  MyCircle seeds1 = {INNER_SEEDS_RADIUS};
  MyCircle seeds2 = {OUTER_SEEDS_RADIUS};
  MyFlower petals1 = {RADIUS, NUMBER_OF_PETALS};
  MyFlower petals2 = {RADIUS, NUMBER_OF_PETALS};
  // MyFlower petals3 = {RADIUS, NUMBER_OF_PETALS};
  // MyFlower petals4 = {RADIUS, NUMBER_OF_PETALS};
};

#endif // ifndef MY_SUNFLOWER_
