#ifndef MY_SCENE_
#define MY_SCENE_

#include "playable.hpp"
#include "timeline.hpp"

class MyScene : public MyPlayable {
public:
  MyScene();
  void play() override;
  void stop() override;
  void toggle() override;
  void add(MyTimeline *);
  bool update(int) override;

protected:
  std::vector<MyTimeline *> timelines;
};

#endif
