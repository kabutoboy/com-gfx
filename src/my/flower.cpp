#include "my/flower.hpp"
#include "my/mathconst.hpp"
#include <cmath>

MyFlower::MyFlower(float r, float petals, int n) {
  if (n == 0) {
    // n = 2. * PI * r;
    n = (int)(16.f * petals);
  }

  vertices.resize(n);

  for (int i = 0; i < n; i++) {
    float angle = 2 * PI * i / n;
    vertices[i].assign({r * sinf(.5f * petals * angle) * cosf(angle),
                        r * sinf(.5f * petals * angle) * sinf(angle)});
  }
}
