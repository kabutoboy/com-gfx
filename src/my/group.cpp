#include "my/drawable.hpp"
#include "my/group.hpp"
#include "my/point.hpp"
#include <iostream>

MyGroup::MyGroup() {
  limitDraw(1);
  useDrawLimit(true);
  totalVertices = 0;
}

void MyGroup::add(MyDrawable *child) {
  children.push_back(child);
  totalVertices += child->size();
}

void MyGroup::draw() {
  if (!usingDrawLimit) {
    for (auto &c : children) {
      c->draw();
    }
    return;
  }

  int limit = (int)(drawLimit * (float)size());
  int drawn = 0;
  // if (drawLimit < 1) std::cout << drawLimit << "\n";
  // if (drawLimit < 1) std::cout << "-----\n";
  for (auto &c : children) {
    int s = c->size();
    if (drawn + s >= limit) {
      c->limitDraw((float)(limit - drawn) / (float)s);
      // std::cout << "limitDraw(" << (float)(drawn - limit) /
      // (float)(c->size()) << ")\n";
      c->draw();
      break;
    }
    c->limitDraw(1);
    c->draw();
    drawn += s;
    // if (drawLimit < 1) std::cout << "drawn: " << drawn << ", limit: " <<
    // limit << "\n";
  }
  // if (drawLimit < 1) std::cout << "-----\n";
}

int MyGroup::size() {
  // int s = 0;
  // for (auto &c : children) {
  //   s += c->size();
  // }
  // return s;
  return totalVertices;
}

void MyGroup::scale(float amount) {
  for (auto &c : children) {
    c->scale(amount);
  }
}

void MyGroup::rotate(float amount) {
  for (auto &c : children) {
    c->rotate(amount);
  }
}

void MyGroup::translate(MyPoint *amount) {
  for (auto &c : children) {
    c->translate(amount);
  }
}

void MyGroup::setScale(float amount) {
  for (auto &c : children) {
    c->setScale(amount);
  }
}

void MyGroup::setAngle(float amount) {
  for (auto &c : children) {
    c->setAngle(amount);
  }
}

void MyGroup::setPosition(MyPoint *amount) {
  for (auto &c : children) {
    c->setPosition(amount);
  }
}

void MyGroup::setAlpha(float amount) {
  for (auto &c : children) {
    c->setAlpha(amount);
  }
}

void MyGroup::setColor(int amount) {
  for (auto &c : children) {
    c->setColor(amount);
  }
}

void MyGroup::scaleColor(int color, float intensity) {
  for (auto &c : children) {
    c->scaleColor(color, intensity);
  }
}

void MyGroup::embedScale() {
  for (auto &c : children) {
    c->embedScale();
  }
}

void MyGroup::embedAngle() {
  for (auto &c : children) {
    c->embedAngle();
  }
}

void MyGroup::embedPosition() {
  for (auto &c : children) {
    c->embedPosition();
  }
}

void MyGroup::limitDraw(float limit) {
  this->drawLimit = limit;
  // std::cout << "drawLimit: " << drawLimit ;
  // for (auto &c : children) {
  //   c->limitDraw(limit);
  // }
}

void MyGroup::useDrawLimit(bool use) { usingDrawLimit = use; }
