#include "my/mathconst.hpp"
#include "my/group.hpp"
#include "my/sunflower.hpp"

MySunFlower::MySunFlower(float scl, float rotation, MyPoint *translation) {
  seeds1.setColor(0x5d4239);
  seeds2.setColor(0x795548);
  petals1.setColor(0xffeb3b);
  petals2.setColor(0xffd219);
  petals3.setColor(0xffdc1e);
  petals4.setColor(0xffc107);
  petals2.rotate(-1 * PI / MySunFlower::NUMBER_OF_PETALS / 2);
  petals3.rotate(1 * PI / MySunFlower::NUMBER_OF_PETALS / 2);
  petals4.rotate(2 * PI / MySunFlower::NUMBER_OF_PETALS / 2);

  add(&petals4);
  add(&petals3);
  add(&petals2);
  add(&petals1);
  add(&seeds2);
  add(&seeds1);

  scale(scl);
  rotate(rotation);
  translate(translation);
}
