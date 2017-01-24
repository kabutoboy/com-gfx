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
  };
}

void MyScene::add(MyTimeline *tl) { timelines.push_back(tl); }

bool MyScene::update(int deltaTime) {
  for (auto &tl : timelines) {
    tl->update(deltaTime);
  }
}
