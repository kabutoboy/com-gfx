#include <cstdlib>
#include <ctime>
#include <iostream>

#include "my/animation.hpp"
#include "my/circle.hpp"
#include "my/ellipse.hpp"
#include "my/group.hpp"
#include "my/man.hpp"
#include "my/mathconst.hpp"
#include "my/point.hpp"
#include "my/rectangle.hpp"
#include "my/scene.hpp"
#include "my/sunflower.hpp"
#include "my/timeline.hpp"
#include <GL/glut.h>

MyGroup all;
MyScene scene;

int displayWidth = 1200;
int displayHeight = 600;
float halfDisplayWidth = 0.5f * (float)displayWidth;
float halfDisplayHeight = 0.5f * (float)displayHeight;

int frameRate = 60;
int frameTime = 1000 / frameRate;
int frameCount = 0;
int currentTime;
int lastTime;
int elapsedTime;
int elapsedTime2;

void init(void) {
  std::srand(std::time(0));

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  // glClearColor(0.2, 0.2, 0.3, 1.0);
  glClearColor(1, 1, 1, 1);

  auto man1 = new MyMan();
  all.add(man1);

  auto tl = new MyTimeline();
  scene.add(tl);
  tl->play();

  tl->add(new MyAnimation(
      [man1](float progress) {
        float t = fmod(progress, 0.25f) / 0.25f;
        man1->setPosition(new MyPoint(
            {displayWidth * (1.2f * progress - 0.1f) - halfDisplayWidth,
             50.0f * abs(sinf(t * TAU))}));
        man1->leg11->setAngle(PI * (2.0f + 0.5f * sinf(t * TAU)));
        man1->leg12->setAngle(PI * (1.8f + 0.7f * sinf(t * TAU)));
        man1->leg21->setAngle(PI * (2.0f + 0.5f * sinf((0.5f + t) * TAU)));
        man1->leg22->setAngle(PI * (1.8f + 0.7f * sinf((0.5f + t) * TAU)));
        man1->arm11->setAngle(PI * (2.0f + 0.5f * sinf(t * TAU)));
        man1->arm12->setAngle(PI * (2.2f + 0.5f * sinf(t * TAU)));
        man1->arm21->setAngle(PI * (2.0f + 0.5f * sinf((0.5f + t) * TAU)));
        man1->arm22->setAngle(PI * (2.2f + 0.5f * sinf((0.5f + t) * TAU)));
        man1->translate(new MyPoint({10 * sinf(2 * (t - 0.05f) * TAU), 0}));
      },
      8000));

  tl->loop(true);

  lastTime = currentTime = glutGet(GLUT_ELAPSED_TIME);
  elapsedTime = 0;

  all.useDrawLimit(false);
  scene.stop();
}

void update() {
  currentTime = glutGet(GLUT_ELAPSED_TIME);
  int deltaTime = currentTime - lastTime;
  lastTime = currentTime;

  elapsedTime += deltaTime;
  elapsedTime2 += deltaTime;
  if (elapsedTime >= frameTime) {
    scene.update(elapsedTime);
    elapsedTime = 0;
  }
  if (elapsedTime2 >= 1000) {
    std::cout << frameCount << "fps\n";
    frameCount = 0;
    elapsedTime2 = 0;
  }
}

void draw() {
  all.draw();
  frameCount++;
}

void onReshape(int width, int height) {
  // GLfloat aspect;

  if (height == 0)
    height = 1;

  // aspect = (GLfloat)width / (GLfloat)height;

  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
  // gluOrtho2D(-halfDisplayWidth, halfDisplayWidth, -halfDisplayHeight,
  //            halfDisplayHeight);
}

void onDisplay() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  update();
  draw();
  glFlush();
  glutSwapBuffers();
}

void onRedisplay() { glutPostRedisplay(); }

void onMouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    scene.toggle();
  }
}

void onTimer(int value) {
  glutPostRedisplay();
  glutTimerFunc(frameTime, onTimer, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(displayWidth, displayHeight);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Test OpenGL");
  init();
  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onReshape);
  // glutIdleFunc(onRedisplay);
  glutTimerFunc(0, onTimer, 0);
  glutMouseFunc(onMouse);
  glutMainLoop();
  return 0;
}
