#include "drawable.h"
#include "point.h"

class MyPolygon : public MyDrawable {

protected:

	vector<MyPoint> vertices;
	MyPoint color;
	MyPoint position;
	float scl;
	float angle;

public:

	MyPolygon();

	// NON-MODIFYING
	void draw() override;

	// MODIFYING
	void setColor(int);
	void setColor(float, float, float);
	void setPosition(float, float);
	void scale(float) override;
	void rotate(float) override;
	void translate(MyPoint*) override;
};
