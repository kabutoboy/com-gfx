#include "point.h"

class Drawable {
public:
	virtual void draw() { }
	virtual void scale(float) = 0;
	virtual void rotate(float) = 0;
	virtual void translate(MyPoint*) = 0;
};
