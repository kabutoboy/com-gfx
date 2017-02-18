#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "Color.hpp"
#include "CreateObject.hpp"
#include "DeviceController.hpp"
#include "MyMath.hpp"
#include "Parameters.hpp"
#include "TimeSettings.hpp"

float speed;
float dTheta = 0.0;

int circleID, rectID1, rectID2;

int head;
int left;
int right;
int body;

int state = 0;

void Start(void) {

  StartTime();

  // circleID = CreateCircle(1.0, BLUE);
  // rectID1 = CreateRectangle(3.0, RED);
  // rectID2 = CreateRectangle(2.0, GREEN);

  head = CreateCircle(1.0, RED);
  left = CreateRectangle(1.0, BLUE);
  right = CreateRectangle(1.0, BLUE);
  body = CreateRectangle(1.0, BLUE);

  speed = 10.0;
  refreshMills = 17;
}

void Update() {

  dTheta = 45.0;
  //
  // glPushMatrix();
  // glCallList(rectID1);
  // glPopMatrix();
  //
  // glPushMatrix();
  // glCallList(rectID2);
  // glPopMatrix();
  //
  // glPushMatrix();
  // glCallList(circleID);
  // glPopMatrix();
  glLoadIdentity();
  glTranslatef(0.25 * sin(4 * elapsedTime * 2 * PI), 0.25 * sin(elapsedTime * 2 * PI), 0);

  glPushMatrix();
  glTranslatef(0.5, 1.8, 0);
  glRotatef(-elapsedTime * 90, 0, 0, 1);
  glScalef(1, 0.2, 1);
  glTranslatef(1, 0, 0);
  glCallList(right);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.5, 1.8, 0);
  glRotatef(elapsedTime * 180, 0, 0, 1);
  glScalef(1, 0.2, 1);
  glTranslatef(1, 0, 0);
  glCallList(left);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.5, 2, 1);
  glCallList(body);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 3, 0);
  // glScalef(0.2, 0.2, 1);
  glCallList(head);
  glPopMatrix();
}

void display(void) {

  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //------------- Time -----------

  // deltaTime = CalculateDeltaTime();
  deltaTime = refreshMills / 1000.0;
  CalculateFrameRate(deltaTime);
  elapsedTime += deltaTime;

  //---------- Update -----------

  Update();

  //-----------------------------

  glFlush();
  glutSwapBuffers();

  //-----------------------------

  //  dTheta += speed*deltaTime;
}

void InitOpenGL() { glClearColor(1.0, 1.0, 1.0, 1.0); }

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(640, 640);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Test OpenGL");

  InitOpenGL();

  Start();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  //  glutIdleFunc(idle);

  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeyboard);

  glutTimerFunc(0, Timer, 0);

  glutMainLoop();

  return 0;
}
