#include "my/drawable.hpp"
#include "my/group.hpp"
#include "my/point.hpp"

MyGroup::MyGroup() {}

void MyGroup::add(MyDrawable *child) { children.push_back(child); }

void MyGroup::draw(float amount) {
  for (auto &c : children) {
    c->draw(amount);
  }
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
