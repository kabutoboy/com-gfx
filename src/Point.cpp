#include <GL/glut.h>
#include "Point.hpp"

Point::Point(){
  x0 = 0.0;
  y0 = 0.0;
}

Point::Point(float x,float y){
  x0 = x;
  y0 = y;
}


void Point::SetPosition(float x,float y){
  x0 = x;
  y0 = y;
}


void Point::Draw(){
  glBegin(GL_POINT); 
   glVertex2f(x0,y0);
  glEnd();
}

