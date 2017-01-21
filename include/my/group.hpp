#ifndef MY_GROUP_
#define MY_GROUP_

#include "drawable.hpp"
#include <vector>

class MyGroup : public MyDrawable {
public:
  MyGroup();
  void add(MyDrawable *);
  void draw(float = 1) override;
  void scale(float) override;
  void rotate(float) override;
  void translate(MyPoint *) override;

protected:
  std::vector<MyDrawable *> children;
};

#endif // ifndef MY_GROUP_
