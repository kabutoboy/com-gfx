#include "my/group.hpp"
#include "my/mathconst.hpp"
#include "my/apple.hpp"

MyApple::MyApple(float scl, float rotation, MyPoint *translation) {
  auto redCircle = new MyCircle(RADIUS);
  redCircle->setColor(0xff0000);

  add(redCircle);

  embedScale();
  embedAngle();
  embedPosition();

  translate(translation);
  rotate(rotation);
  scale(scl);
}
