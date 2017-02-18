#include "Shape.hpp"
#include <GL/glut.h>

void Shape::SetPosition(float x,float y){
  x0 = x;
  y0 = y;
}


void Shape::SetColor(double r,double g,double b){
  glColor3f(r, g, b);
}


void Shape::SetColor(Color color){

  if(color == RED)
    glColor3fv(red);
  else if(color == GREEN)
    glColor3fv(green);
  else if(color == BLUE)
    glColor3fv(blue);
  else if(color == WHITE)
    glColor3fv(white);
  else if(color == BLACK)
    glColor3fv(black);

}

void Shape::Translate(float x,float y,float z){

  glTranslatef(x,y,z);

}


void Shape::Rotate(float angle){

  glRotatef(angle,0,0,1);

}

void Shape::Scale(float sx,float sy){

  glScalef(sx,sy,0.0);

}

