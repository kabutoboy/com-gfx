#ifndef MY_POLYGON_
#define MY_POLYGON_

#include "drawable.hpp"
#include "point.hpp"

class MyPolygon : public MyDrawable {
public:
  MyPolygon();

  // NON-MODIFYING
  void draw(float = 1) override;

  // MODIFYING
  void setColor(int);
  void setColor(float, float, float);
  void setAlpha(float);
  void setPosition(float, float);
  void scale(float) override;
  void rotate(float) override;
  void translate(MyPoint *) override;
  void setScale(float) override;
  void setAngle(float) override;
  void setPosition(MyPoint *) override;
  void embedScale() override;
  void embedAngle() override;
  void embedPosition() override;

protected:
  std::vector<MyPoint> vertices;
  MyPoint color;
  MyPoint position;
  float scl;
  float angle;
  float angleCos;
  float angleSin;
  float alpha;
};

#endif // ifndef MY_POLYGON_
