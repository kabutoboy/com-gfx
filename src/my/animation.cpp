#include "my/animation.hpp"

// MyAnimation::MyAnimation(MyDrawable *actor,
//                          std::function<void(MyDrawable *, float)> action,
//                          int totalTime) {
MyAnimation::MyAnimation(std::function<void(float)> action, int totalTime) {
  this->action = action;
  this->totalTime = totalTime;
  this->elapsedTime = 0;
}

void MyAnimation::restart() { elapsedTime = 0; }

bool MyAnimation::update(int deltaTime) {
  elapsedTime += deltaTime;
  float progress = (float)elapsedTime / (float)totalTime;
  if (progress >= 1) {
    progress = 1;
  }
  this->action(progress);
  return progress >= 1;
}
