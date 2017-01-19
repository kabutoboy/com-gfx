#include <algorithm>

#include <GL/glut.h>
#include "my/polygon.hpp"

MyPolygon::MyPolygon() {
  // vertices = {};
  color.assign({ 0, 0, 0 });
  position.assign({ 0, 0 });
  scl   = 1;
  angle = 0;
}

// NON-MODIFYING
void MyPolygon::draw() {
  // glBegin(GL_LINES);
  glBegin(GL_POLYGON);
  glColor3f(color.at(0), color.at(1), color.at(2));

  for (MyPoint v: vertices) {
    glVertex2f(v.at(0), v.at(1));
  }
  glEnd();
}

// MODIFYING
void MyPolygon::setColor(int hex) {
  color.assign({
    (float)(0xFF & (hex >> 16)) / 255,
    (float)(0xFF & (hex >> 8)) / 255,
    (float)(0xFF & (hex)) / 255
  });
}

void MyPolygon::setColor(float r, float g, float b) {
  color.assign({ r, g, b });
}

void MyPolygon::setPosition(float x, float y) {
  position.assign({ x, y });
}

void MyPolygon::scale(float amount) {
  this->scl *= amount;
  MyPoint *pos = &position;
  for_each(vertices.begin(), vertices.end(), [amount, pos](MyPoint& v) {
    v.scale(amount, pos);
  });
}

void MyPolygon::rotate(float amount) {
  this->angle += amount;
  for_each(vertices.begin(), vertices.end(), [amount](MyPoint& v) {
    float x = v.at(0), y = v.at(1);
    v.set(0, x * cos(amount) - y * sin(amount));
    v.set(1, x * sin(amount) + y * cos(amount));

    // v.set(0, fma(x, cos(amount), -y * sin(amount)));
    // v.set(1, fma(x, sin(amount), +y * cos(amount)));
  });
}

void MyPolygon::translate(MyPoint *amount) {
  this->position.add(amount);
  for_each(vertices.begin(), vertices.end(), [amount](MyPoint& v) {
    v.add(amount);
  });
}
