#ifndef MY_ANIMATION_
#define MY_ANIMATION_

#include <functional>

#include "drawable.hpp"

class MyAnimation {
public:
  MyAnimation(MyDrawable *, std::function<void(MyDrawable *, float)>, int);
  // MyAnimation(MyDrawable *, void (*)(MyDrawable *, float), int);
  bool update(int);
  void restart();

protected:
  MyDrawable *actor;
  std::function<void(MyDrawable *, float)> action;
  // void (*action)(MyDrawable *, float);
  int elapsedTime;
  int totalTime;
};

#endif
