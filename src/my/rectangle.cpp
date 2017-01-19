#include "my/rectangle.hpp"

MyRectangle::MyRectangle(float w, float h) {
  vertices.resize(4);
  vertices[0].assign({ (float).5 * (-w), (float).5 * (-h) });
  vertices[1].assign({ (float).5 * (+w), (float).5 * (-h) });
  vertices[2].assign({ (float).5 * (+w), (float).5 * (+h) });
  vertices[3].assign({ (float).5 * (-w), (float).5 * (+h) });
}
