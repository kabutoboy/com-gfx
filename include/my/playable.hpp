#ifndef MY_PLAYABLE_
#define MY_PLAYABLE_

class MyPlayable {
public:
  virtual void play() = 0;
  virtual void stop() = 0;
  virtual bool update(int) = 0;
};

#endif
