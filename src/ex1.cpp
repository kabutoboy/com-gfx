#include <iostream>

#include "my/animation.hpp"
#include "my/circle.hpp"
#include "my/group.hpp"
#include "my/mathconst.hpp"
#include "my/point.hpp"
#include "my/scene.hpp"
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
int currentTime;
int lastTime;
int elapsedTime;

void init(void) {

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glClearColor(0.2, 0.2, 0.3, 1.0);
  gluOrtho2D(-halfDisplayWidth, halfDisplayWidth, -halfDisplayHeight,
             halfDisplayHeight);

  MyCircle *myCircle = new MyCircle(70, 8);
  myCircle->setColor(0xff0000);
  all.add(myCircle);

  auto *tl = new MyTimeline();
  tl->add(new MyAnimation(
      [myCircle](float progress) {
        myCircle->setScale(1.0f + 0.2f * sinf(TAU * progress));
      },
      1000));
  tl->loop(true);
  scene.add(tl);


  lastTime = currentTime = glutGet(GLUT_ELAPSED_TIME);
  elapsedTime = 0;

  scene.stop();
}

void update() {
  currentTime = glutGet(GLUT_ELAPSED_TIME);
  int deltaTime = currentTime - lastTime;
  lastTime = currentTime;

  elapsedTime += deltaTime;
  if (elapsedTime >= frameTime) {
    scene.update(elapsedTime);
    elapsedTime = 0;
  }
}

void draw() { all.draw(); }

void onDisplay() {
  glClear(GL_COLOR_BUFFER_BIT);
  update();
  draw();
  glFlush();
  glutSwapBuffers();
}

void onRedisplay() { glutPostRedisplay(); }

void onMouse(int button, int state, int x, int y) {
  switch (button) {
  case GLUT_LEFT_BUTTON:
    scene.play();
    break;
  default:
    break;
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(displayWidth, displayHeight);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Example 1");
  init();
  glutDisplayFunc(onDisplay);
  glutIdleFunc(onRedisplay);
  glutMouseFunc(onMouse);
  glutMainLoop();
  return 0;
}
