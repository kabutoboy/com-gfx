#include <GL/glut.h>
#include <math.h>

#include "MyMath.hpp"
#include "Circle.hpp"


Circle::Circle(){
    radius = 1.0;
    x0 = 0.0;
    y0 = 0.0;
}

Circle::Circle(float r,float x,float y){
    radius = r;
    x0 = x;
    y0 = y;
}

void Circle::SetRadius(float r){
  radius = r;
}

void Circle::Draw(){
	int i,n;
	float x,y,theta;

	n = 40;

	glBegin(GL_POLYGON); 

	
	for(i = 0; i < n; i++){
	  theta = 2.0*PI*i/n;  
	  x = x0 + radius*cos(theta);
	  y = y0 + radius*sin(theta);
	  glVertex2f(x,y);
	}

	glEnd();

}

