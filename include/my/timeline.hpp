#ifndef MY_TIMELINE_
#define MY_TIMELINE_

#include "animation.hpp"
#include "playable.hpp"

class MyTimeline : public MyPlayable {
public:
  MyTimeline(int = 60);
  void play() override;
  void stop() override;
  void toggle() override;
  void loop(bool looping);
  void add(MyAnimation *);
  void setFrameRate(int);
  void setRepeatFrame(int);
  bool update(int) override;

protected:
  std::vector<MyAnimation *> playlist;
  unsigned index;
  unsigned repeatAt;
  unsigned frameRate;
  unsigned frameTime;
  unsigned elapsedTime;
  bool playing;
  bool looping;
  bool finished;
};

#endif
