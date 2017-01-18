#include <cmath>

#include "my/ellipse.hpp"
#include "my/mathconst.hpp"

MyEllipse::MyEllipse(float a, float b, int n) {
	if (n == 0) {
		// n = 2. * PI * r;
		n = 20;
	}
	vertices.resize(n);
	for (int i = 0; i < n; i++) {
		float angle = 2 * PI * i / n;
		vertices[i].assign({a * cos(angle), b * sin(angle)});
	}
}
