#include "my/circle.hpp"
#include "my/mathconst.hpp"

MyCircle::MyCircle(float r, int n) {
  if (n == 0) {
    // n = 2. * PI * r;
    n = 20;
  }
  vertices.resize(n);

  for (int i = 0; i < n; i++) {
    float angle = 2 * PI * i / n;
    vertices[i].assign({ r *cos(angle), r * sin(angle) });
  }
}
