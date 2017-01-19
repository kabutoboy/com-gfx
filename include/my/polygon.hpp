#ifndef MY_POLYGON_
#define MY_POLYGON_

#include "drawable.hpp"
#include "point.hpp"

using namespace std;

class MyPolygon : public MyDrawable {
public:

  MyPolygon();

  // NON-MODIFYING
  void draw() override;

  // MODIFYING
  void setColor(int);
  void setColor(float,
                float,
                float);
  void setPosition(float,
                   float);
  void scale(float) override;
  void rotate(float) override;
  void translate(MyPoint *) override;

protected:

  vector<MyPoint>vertices;
  MyPoint color;
  MyPoint position;
  float scl;
  float angle;
};

#endif // ifndef MY_POLYGON_
