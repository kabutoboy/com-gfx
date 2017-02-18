#include <stdio.h>
#include <GL/glut.h>

#include "Color.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"

int CreateCircle(float radius,Color color){

  Circle circle;
  int id;

  circle.SetRadius(radius);

  id = glGenLists(1);

  glNewList(id, GL_COMPILE);
    circle.SetColor(color);
    circle.Draw();
  glEndList();

  printf("circle : %d\n",id);

  return id;
}

int CreateRectangle(float size,Color color){

  Rectangle rectangle;
  int id;

  rectangle.SetSize(size);

  id = glGenLists(1);

  glNewList(id, GL_COMPILE);
    rectangle.SetColor(color);
    rectangle.Draw();
  glEndList();

  printf("rectangle : %d\n",id);
  
  return id;

}

