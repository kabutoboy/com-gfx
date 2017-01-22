#include "my/animation.hpp"

MyAnimation::MyAnimation(MyDrawable *actor, void (*action)(MyDrawable *, float),
                         int totalTime) {
  this->actor = actor;
  this->action = action;
  this->totalTime = totalTime;
  this->elapsedTime = 0;
}

bool MyAnimation::update(int deltaTime) {
  elapsedTime += deltaTime;
  float progress = (float)elapsedTime / (float)totalTime;
  if (progress >= 1) {
    progress = 1;
  }
  this->action(actor, progress);
  return progress >= 1;
}
