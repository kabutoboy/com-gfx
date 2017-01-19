#ifndef MY_GROUP_
#define MY_GROUP_

#include <vector>
#include "drawable.hpp"

class MyGroup : public MyDrawable {
public:

  MyGroup();
  void add(MyDrawable *);
  void draw() override;
  void scale(float) override;
  void rotate(float) override;
  void translate(MyPoint *) override;

protected:

  vector<MyDrawable *>children;
};

#endif // ifndef MY_GROUP_
