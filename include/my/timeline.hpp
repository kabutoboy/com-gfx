#ifndef MY_TIMELINE_
#define MY_TIMELINE_

#include "animation.hpp"
#include "playable.hpp"

class MyTimeline : public MyPlayable {
public:
  MyTimeline(int = 60);
  void play() override;
  void stop() override;
  void loop(bool looping);
  void add(MyAnimation *);
  void setFrameRate(int);
  bool update(int) override;

protected:
  std::vector<MyAnimation *> playlist;
  int index;
  int frameRate;
  int frameTime;
  int elapsedTime;
  bool playing;
  bool looping;
  bool finished;
};

#endif
