#include "my/scene.hpp"

MyScene::MyScene() {}

void MyScene::play() {
  for (auto &tl : timelines) {
    tl->play();
  }
}

void MyScene::stop() {
  for (auto &tl : timelines) {
    tl->stop();
  }
}

void MyScene::toggle() {
  for (auto &tl : timelines) {
    tl->toggle();
  }
}

void MyScene::add(MyTimeline *tl) { timelines.push_back(tl); }

bool MyScene::update(int deltaTime) {
  bool allFinished = true;
  for (auto &tl : timelines) {
    bool finished = tl->update(deltaTime);
    allFinished = allFinished && finished;
  }
  return allFinished;
}
