#include <iostream>

#include <GL/glut.h>
#include "my/mathconst.hpp"
#include "my/circle.hpp"
#include "my/ellipse.hpp"
#include "my/group.hpp"
#include "my/point.hpp"
#include "my/rectangle.hpp"
#include "my/sunflower.hpp"

using namespace std;

MyGroup all;

int displayWidth = 600;
int displayHeight = 600;

void init(void)
{
	glClearColor(0.2, 0.2, 0.3, 1.0);
	gluOrtho2D(-250, 250.0, -250.0, 250.0);

	MyRectangle *sky = new MyRectangle(600, 600);
	sky->setColor(0xafe0f7);
	all.add(sky);

	MyCircle *sunGlow3 = new MyCircle(130, 130);
	sunGlow3->setColor(0xc0e7f9);
	sunGlow3->translate(new MyPoint({0, 100}));

	MyCircle *sunGlow2 = new MyCircle(100, 100);
	sunGlow2->setColor(0xdef2fc);
	sunGlow2->translate(new MyPoint({0, 100}));

	MyCircle *sunGlow1 = new MyCircle(80, 80);
	sunGlow1->setColor(0xf0f9fe);
	sunGlow1->translate(new MyPoint({0, 100}));

	MyCircle *sunCenter = new MyCircle(70, 70);
	sunCenter->setColor(0xffffff);
	sunCenter->translate(new MyPoint({0, 100}));

	MyGroup *sun = new MyGroup();
	sun->add(sunGlow3);
	sun->add(sunGlow2);
	sun->add(sunGlow1);
	sun->add(sunCenter);

	sun->add(new MySunFlower(.6, 0, new MyPoint({0, 100})));

	all.add(sun);

	MyEllipse *cloud22 = new MyEllipse(30, 15, 70);
	cloud22->setColor(0xfffffc);
	cloud22->translate(new MyPoint({140, 180}));

	MyEllipse *cloud21 = new MyEllipse(40, 20, 70);
	cloud21->setColor(0xfffffc);
	cloud21->translate(new MyPoint({100, 190}));

	MyGroup *cloud2 = new MyGroup();
	cloud2->add(cloud22);
	cloud2->add(cloud21);
	all.add(cloud2);

	MyEllipse *cloud12 = new MyEllipse(50, 20, 70);
	cloud12->setColor(0xfffffc);
	cloud12->translate(new MyPoint({-150, 140}));

	MyEllipse *cloud11 = new MyEllipse(40, 20, 70);
	cloud11->setColor(0xfffffc);
	cloud11->translate(new MyPoint({-100, 150}));

	MyGroup *cloud1 = new MyGroup();
	cloud1->add(cloud12);
	cloud1->add(cloud11);
	all.add(cloud1);

	MyRectangle *grass = new MyRectangle(600, 400);
	grass->setColor(0x67754c);
	// grass->setColor(0x795548);
	grass->translate(new MyPoint({0, -100}));
	all.add(grass);

	int m = 20, n = 80;
	for (int i = 0; i < m; i++) {
		MyGroup *row = new MyGroup();
		for (int j = 0; j < n; j++) {
			float r = MySunFlower::RADIUS;
			float scl = displayWidth / (2 * r) / n * 8;
			MySunFlower *sunFlower = new MySunFlower{
        scl,
        2 * PI * (i + j) / (m + n),
        new MyPoint({
          scl * 2 * r * (n/2 - j) * ((float)(i+1) / m),
          (float)(100 - 1 * i * i)
        })
      };
			row->add(sunFlower);
		}
		row->scale((float)(i+1) / m);
		all.add(row);
	}
}

void draw()
{
	all.draw();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(displayWidth, displayHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Test OpenGL");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
