#ifndef MY_TIMELINE_
#define MY_TIMELINE_

#include "animation.hpp"

class MyTimeline {
public:
  MyTimeline(int = 60);
  void play();
  void stop();
  void add(MyAnimation *);
  void setFrameRate(int);
  bool update(int);

protected:
  std::vector<MyAnimation *> playlist;
  int index;
  int frameRate;
  int frameTime;
  int elapsedTime;
  bool playing;
};

#endif
