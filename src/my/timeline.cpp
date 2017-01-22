#include "my/timeline.hpp"
#include <iostream>

MyTimeline::MyTimeline(int frameRate) {
  this->setFrameRate(frameRate);
  this->elapsedTime = 0;
  this->playing = false;
  this->index = 0;
}

void MyTimeline::play() { playing = true; }

void MyTimeline::stop() { playing = false; }

void MyTimeline::add(MyAnimation *anim) { playlist.push_back(anim); }

void MyTimeline::setFrameRate(int frameRate) {
  this->frameRate = frameRate;
  this->frameTime = 1000 / frameRate;
}

bool MyTimeline::update(int deltaTime) {
  if (index >= playlist.size()) { // end of list
    return true;
  }
  if (!playing) {
    return false;
  }
  elapsedTime += deltaTime;
  if (elapsedTime >= frameTime) { // for capping fps
    // int elapsedFrames = elapsedTime / frameTime;
    auto *anim = playlist.at(index);
    bool next = anim->update(elapsedTime);
    if (next) {
      ++index;
    }
    elapsedTime = 0;
  }
  return false;
}
