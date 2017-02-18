#include <GL/glut.h>
#include <math.h>

#include "Rectangle.hpp"



Rectangle::Rectangle(){
  size = 1.0;
}

Rectangle::Rectangle(float s){
  size = s;
}

void Rectangle::Draw(){

	glBegin(GL_POLYGON); 
	  glVertex2f(x0-size,y0-size);
	  glVertex2f(x0+size,y0-size);
	  glVertex2f(x0+size,y0+size);
	  glVertex2f(x0-size,y0+size);
	glEnd();

}

void Rectangle::SetSize(float s){
  size = s;
}

