#ifndef MY_ANIMATION_
#define MY_ANIMATION_

#include <functional>

#include "drawable.hpp"

class MyAnimation {
public:
  MyAnimation(std::function<void(float)>, int);
  // MyAnimation(MyDrawable *, std::function<void(MyDrawable *, float)>, int);
  bool update(int);
  void restart();

protected:
  // MyDrawable *actor;
  // std::function<void(MyDrawable *, float)> action;
  std::function<void(float)> action;
  int elapsedTime;
  int totalTime;
};

#endif
