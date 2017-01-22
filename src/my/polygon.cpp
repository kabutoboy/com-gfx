#include <algorithm>
#include <cmath>

#include "my/polygon.hpp"
#include <GL/glut.h>

MyPolygon::MyPolygon() {
  // vertices = {};
  color.assign({0, 0, 0});
  position.assign({0, 0});
  scl = 1;
  angle = 0;
}

// NON-MODIFYING
void MyPolygon::draw(float amount) {
  // glBegin(GL_LINES);
  glBegin(GL_POLYGON);
  glColor3f(color.at(0), color.at(1), color.at(2));
  std::vector<MyPoint> V(vertices);
  for (int i = 0, n = (int)(amount * (float)V.size()); i < n; i++) {
    auto &v = V.at(i);
    float x = v.at(0);
    float y = v.at(1);
    float center_x = this->position.at(0);
    float center_y = this->position.at(1);
    x += center_x;
    y += center_y;
    float _x = x;
    float _y = y;
    x = _x * cosf(this->angle) - _y * sinf(this->angle);
    y = _x * sinf(this->angle) + _y * cosf(this->angle);
    x = center_x + this->scl * (x - center_x);
    y = center_y + this->scl * (y - center_y);
    glVertex2f(x, y);
  }
  // for (int i = 0, n = (int)(amount * (float)vertices.size()); i < n; i++) {
  //   auto &v = vertices.at(i);
  //   glVertex2f(v.at(0), v.at(1));
  // }
  glEnd();
}

// MODIFYING
void MyPolygon::setColor(int hex) {
  color.assign({(float)(0xFF & (hex >> 16)) / 255.f,
                (float)(0xFF & (hex >> 8)) / 255.f,
                (float)(0xFF & (hex)) / 255.f});
}

void MyPolygon::setColor(float r, float g, float b) { color.assign({r, g, b}); }

void MyPolygon::setPosition(float x, float y) { position.assign({x, y}); }

void MyPolygon::scale(float amount) {
  this->scl = amount;
  // this->scl *= amount;
  // MyPoint *pos = &position;
  // for_each(vertices.begin(), vertices.end(),
  //          [amount, pos](MyPoint &v) { v.scale(amount, pos); });
}

void MyPolygon::rotate(float amount) {
  this->angle = amount;
  // this->angle += amount;
  // for_each(vertices.begin(), vertices.end(), [amount](MyPoint &v) {
  //   float x = v.at(0), y = v.at(1);
  //   v.set(0, x * cosf(amount) - y * sinf(amount));
  //   v.set(1, x * sinf(amount) + y * cosf(amount));
  // });
}

void MyPolygon::translate(MyPoint *amount) {
  this->position = *amount;
  // this->position.add(amount);
  // for_each(vertices.begin(), vertices.end(),
  //          [amount](MyPoint &v) { v.add(amount); });
}
