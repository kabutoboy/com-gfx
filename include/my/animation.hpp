#ifndef MY_ANIMATION_
#define MY_ANIMATION_

#include "drawable.hpp"

class MyAnimation {
public:
  MyAnimation(MyDrawable *, void (*)(MyDrawable *, float), int);
  bool update(int);

protected:
  MyDrawable *actor;
  void (*action)(MyDrawable *, float);
  int elapsedTime;
  int totalTime;
};

#endif
