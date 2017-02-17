#ifndef MY_POINT_
#define MY_POINT_

#include <initializer_list>
#include <string>
#include <vector>

class MyPoint {
public:
  MyPoint();
  MyPoint(std::initializer_list<float>);
  MyPoint(std::vector<float>);

  // NON-MODIFYING
  float at(int);
  int size();
  auto begin();
  auto end();
  MyPoint *copy();
  void dump(std::string = "");

  // MODIFYING
  void assign(std::initializer_list<float>);
  void assign(std::vector<float>);
  void resize(int);
  void set(int, float);
  void scale(float, MyPoint *);
  MyPoint *add(MyPoint *);
  MyPoint *sub(MyPoint *);
  MyPoint *abs();
  MyPoint *pow(float);
  float sum();

  // STATIC
  static MyPoint *add(MyPoint *, MyPoint *);
  static MyPoint *sub(MyPoint *, MyPoint *);
  static MyPoint *subAbs(MyPoint *, MyPoint *);
  static MyPoint *pow(MyPoint *, float);
  static MyPoint *rgb(int);
  static float sum(MyPoint *);

protected:
  std::vector<float> data;
};

#endif // ifndef MY_POINT_
