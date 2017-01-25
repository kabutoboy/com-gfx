#ifndef MY_POLYGON_
#define MY_POLYGON_

#include "drawable.hpp"
#include "point.hpp"

class MyPolygon : public MyDrawable {
public:
  MyPolygon();

  // NON-MODIFYING
  void draw() override;
  int size() override;

  // MODIFYING
  void setColor(int) override;
  void setColor(float, float, float);
  void setColor(MyPoint *);
  void scaleColor(int, float) override;
  void setAlpha(float) override;
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
  void limitDraw(float) override;
  void useDrawLimit(bool) override;

protected:
  std::vector<MyPoint> vertices;
  MyPoint color;
  MyPoint position;
  float scl;
  float angle;
  float angleCos;
  float angleSin;
  float alpha;
  float drawLimit;
  bool usingDrawLimit;
};

#endif // ifndef MY_POLYGON_
