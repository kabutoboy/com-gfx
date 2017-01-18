#include <cmath>
#include "my/mathconst.hpp"
#include "my/flower.hpp"

MyFlower::MyFlower(float r, float petals, int n) {
	if (n == 0) {
		// n = 2. * PI * r;
		n = 160;
	}
	vertices.resize(n);
	for (int i = 0; i < n; i++) {
		float angle = 2 * PI * i / n;
		vertices[i].assign({
			r * sin((float).5 * petals * angle) * cos(angle),
			r * sin((float).5 * petals * angle) * sin(angle)
		});
	}
}
