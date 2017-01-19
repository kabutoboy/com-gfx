#include "my/rectangle.hpp"

MyRectangle::MyRectangle(float w, float h) {
  vertices.resize(4);
  vertices[0].assign({.5f * -w, .5f * -h});
  vertices[1].assign({.5f * w, .5f * -h});
  vertices[2].assign({.5f * w, .5f * h});
  vertices[3].assign({.5f * -w, .5f * h});
}
