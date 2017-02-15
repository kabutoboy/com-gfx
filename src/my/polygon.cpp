#include <algorithm>
#include <cmath>

#include "my/mathconst.hpp"
#include "my/polygon.hpp"
#include <GL/glut.h>

MyPolygon::MyPolygon() {
  setColor(0x000000);
  setPosition(0, 0);
  setScale(1);
  setAngle(0);
  setAlpha(1);
  limitDraw(1);
  useDrawLimit(true);
}

// NON-MODIFYING
void MyPolygon::draw() {
  // glBegin(GL_LINES);
  if (changed) {
    id = glGenLists(1);
    glNewList(id, GL_COMPILE);
    glBegin(GL_POLYGON);
    glColor4f(color.at(0), color.at(1), color.at(2), alpha);
    std::vector<MyPoint> &V(vertices);
    int n = usingDrawLimit ? (int)(drawLimit * (float)V.size()) : V.size();
    for (int i = 0; i < n; i++) {
      auto &v = V.at(i);
      float x = v.at(0);
      float y = v.at(1);
      // // rotate before translation because we assume it is centered at (0, 0)
      // float _x = x;
      // float _y = y;
      // x = _x * this->angleCos - _y * this->angleSin;
      // y = _x * this->angleSin + _y * this->angleCos;
      // // translate
      // float center_x = this->position.at(0);
      // float center_y = this->position.at(1);
      // // scale
      // x = center_x + this->scl * x;
      // y = center_y + this->scl * y;
      glVertex2f(x, y);
    }
    glEnd();
    glEndList();
    changed = false;
  }
  glPushMatrix();
  glTranslatef(position.at(0), position.at(1), 0);
  glRotatef(360.0f * angle / TAU, 0, 0, 1);
  glScalef(scl, scl, 1);
  // glScalef(scl.at(0), scl.at(1), scl.at(2));
  // glTranslatef(position.at(0), position.at(1), position.at(2));
  // glRotatef(angle.at(0), angle.at(1), angle.at(2), angle.at(3));
  glCallList(id);
  glPopMatrix();
}

int MyPolygon::size() { return vertices.size(); }

// MODIFYING
void MyPolygon::setColor(int hex) {
  this->setColor(MyPoint::rgb(hex));
  this->changed = true;
}

void MyPolygon::setColor(float r, float g, float b) {
  color.assign({r, g, b});
  this->changed = true;
}

void MyPolygon::scaleColor(int hex, float intensity) {
  MyPoint *color = MyPoint::rgb(hex);
  color->scale(intensity, &this->color);
  this->color = *color;
  this->changed = true;
}

void MyPolygon::setColor(MyPoint *color) {
  this->color = *color;
  this->changed = true;
}

void MyPolygon::setAlpha(float a) {
  this->alpha = a;
  this->changed = true;
}

void MyPolygon::setPosition(float x, float y) {
  position.assign({x, y});
  this->changed = true;
}

void MyPolygon::scale(float amount) {
  this->setScale(this->scl * amount);
  this->changed = true;
}

void MyPolygon::rotate(float amount) {
  this->setAngle(this->angle + amount);
  this->changed = true;
}

void MyPolygon::translate(MyPoint *amount) {
  this->position.add(amount);
  this->changed = true;
}

void MyPolygon::setScale(float amount) {
  this->scl = amount;
  this->changed = true;
}

void MyPolygon::setAngle(float amount) {
  this->angle = amount;
  this->angleCos = cosf(this->angle);
  this->angleSin = sinf(this->angle);
  this->changed = true;
}

void MyPolygon::setPosition(MyPoint *amount) {
  this->position = *amount;
  this->changed = true;
}

void MyPolygon::embedScale() {
  float amount = this->scl;
  MyPoint *pos = &this->position;
  for_each(vertices.begin(), vertices.end(),
           [amount, pos](MyPoint &v) { v.scale(amount, pos); });
  setScale(1);
}

void MyPolygon::embedAngle() {
  float amount = this->angle;
  for_each(vertices.begin(), vertices.end(), [amount](MyPoint &v) {
    float x = v.at(0);
    float y = v.at(1);
    float a = cosf(amount);
    float b = sinf(amount);
    v.set(0, x * a - y * b);
    v.set(1, x * b + y * a);
  });
  setAngle(0);
}

void MyPolygon::embedPosition() {
  MyPoint *amount = &this->position;
  for_each(vertices.begin(), vertices.end(),
           [amount](MyPoint &v) { v.add(amount); });
  setPosition(0, 0);
}

void MyPolygon::limitDraw(float limit) { this->drawLimit = limit; }

void MyPolygon::useDrawLimit(bool use) { this->usingDrawLimit = use; }

MyPoint *MyPolygon::getPosition() {
  return this->position.copy();
}
