#include <iostream>

#include "my/animation.hpp"
#include "my/circle.hpp"
#include "my/ellipse.hpp"
#include "my/group.hpp"
#include "my/mathconst.hpp"
#include "my/point.hpp"
#include "my/rectangle.hpp"
#include "my/scene.hpp"
#include "my/sunflower.hpp"
#include "my/timeline.hpp"
#include <GL/glut.h>

MyGroup all;
MyScene scene;

int displayWidth = 600;
int displayHeight = 600;

int frameRate = 60;               // frames per sec
int frameTime = 1000 / frameRate; // millisecs per frame

int totalFrames = 600;
int currentFrame = 0;

int currentTime;
int lastTime;
int elapsedTime;

void init(void) {
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

  // MySunFlower *sunFlower = new MySunFlower(.6f, 0, new MyPoint({0, 100}));
  // all.add(sunFlower);
  //
  // tl1->add(new MyAnimation(sunFlower,
  //                              [](auto *sf, float progress) {
  //                               //  std::cout << progress << "\n";
  //                                sf->setScale(progress);
  //                                sf->rotate(2*PI * progress);
  //                               // sf->scale(0.5f);
  //                              },
  //                              1000));

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

  MyTimeline *tl1 = new MyTimeline();
  scene.add(tl1);
  tl1->play();

  std::vector<MyGroup *> sunFlowerRows;
  int m = 20, n = 80;
  for (int i = 0; i < m; i++) {
    MyGroup *row = new MyGroup();
    sunFlowerRows.push_back(row);
    float r = MySunFlower::RADIUS;
    float scl = displayWidth / (2 * r) / n * 8;
    float rowScale = (float)(i + 1) / (float)m;
    float displayScale = scl * rowScale;

    for (int j = 0; j < n; j++) {
      // std::cout << rowScale * scl << " ";
      float x = scl * 2 * r * (n / 2 - j) * ((float)(i + 1) / m);
      float y = 100.f - 1.f * i * i;
      if (x < -.5f * displayWidth || x > .5f * displayWidth ||
          y < -.5f * displayHeight || y > .5f * displayHeight) {
        continue;
      }
      MySunFlower *sunFlower =
          new MySunFlower{0, 2 * PI * (i + j) / (m + n), new MyPoint({x, y})};
      row->add(sunFlower);
      // auto fn = [displayScale](MyDrawable *sf, float progress) {
      //   //  std::cout << progress << "\n";
      //   sf->setScale(displayScale * progress);
      //   // sf->scale(0.5f);
      // };
      // tl1->add(new MyAnimation(sunFlower, fn, (int)(rowScale * 100.f)));
    }
    // std::cout << "\n";
    // row->scale(rowScale);
    all.add(row);
    tl1->add(new MyAnimation(
        [row, displayScale](float progress) {
          row->setScale(displayScale * progress);
        },
        (int)(rowScale * 1000.f)));
  }

  MyRectangle *darkness = new MyRectangle(600, 600);
  darkness->setColor(0x000000);
  darkness->setAlpha(.5f);
  all.add(darkness);

  MyTimeline *tl2 = new MyTimeline();
  scene.add(tl2);
  tl2->play();

  tl2->add(new MyAnimation(
      [sun, darkness](float progress) {
        sun->setScale(1 * progress);
        darkness->setAlpha(.5f - .5f * progress);
      },
      5000));

  lastTime = currentTime = glutGet(GLUT_ELAPSED_TIME);
  elapsedTime = 0;

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
}

void draw() {
  currentTime = glutGet(GLUT_ELAPSED_TIME);
  int deltaTime = currentTime - lastTime;
  // elapsedTime += deltaTime;
  lastTime = currentTime;

  scene.update(deltaTime);

  // if (elapsedTime >= frameTime) {// next frame
  // ++currentFrame;
  // currentFrame = (elapsedTime/frameTime + currentFrame);
  // if (currentFrame < totalFrames) {
  //   all.draw((float)currentFrame / (float)totalFrames);
  // } else {
  all.draw();
  //   }
  //   elapsedTime = 0;
  // }
  // std::cout << "deltaTime: " << deltaTime << "\n";
  // std::cout << "elapsedTime: " << elapsedTime << "\n";
  // std::cout << "currentFrame: " << currentFrame << "\n";
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  draw();
  glFlush();
  glutSwapBuffers();
}

void redisplay() { glutPostRedisplay(); }

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(displayWidth, displayHeight);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Test OpenGL");
  init();
  glutDisplayFunc(display);
  glutIdleFunc(redisplay);
  glutMainLoop();
  return 0;
}
