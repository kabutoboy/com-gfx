#ifndef MY_GROUP_
#define MY_GROUP_

#include "drawable.hpp"
#include "point.hpp"
#include <vector>

class MyGroup : public MyDrawable {
public:
  MyGroup();
  void add(MyDrawable *);
  void draw() override;
  int size() override;
  void scale(float) override;
  void rotate(float) override;
  void translate(MyPoint *) override;
  void setScale(float) override;
  void setAngle(float) override;
  void setPosition(MyPoint *) override;
  void setAlpha(float) override;
  void setColor(int) override;
  void scaleColor(int, float) override;
  void embedScale() override;
  void embedAngle() override;
  void embedPosition() override;
  void limitDraw(float) override;
  void useDrawLimit(bool) override;
  MyPoint *getPosition() override;

protected:
  std::vector<MyDrawable *> children;
  MyPoint position;
  float angle;
  float drawLimit;
  int totalVertices;
  bool usingDrawLimit;
};

#endif // ifndef MY_GROUP_
