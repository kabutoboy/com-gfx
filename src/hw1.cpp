#include <cstdlib>
#include <ctime>
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

int displayWidth = 1200;
int displayHeight = 600;
float halfDisplayWidth = .5f * (float)displayWidth;
float halfDisplayHeight = .5f * (float)displayHeight;

int currentTime;
int lastTime;

void init(void) {
  std::srand(std::time(0));

  glClearColor(0.2, 0.2, 0.3, 1.0);
  gluOrtho2D(-halfDisplayWidth, halfDisplayWidth, -halfDisplayHeight,
             halfDisplayHeight);

  MyRectangle *sky = new MyRectangle(displayWidth, displayHeight);
  sky->setColor(0xafe0f7);
  all.add(sky);

  MyCircle *sunGlow3 = new MyCircle(130, 130);
  // sunGlow3->setColor(0xc0e7f9);
  sunGlow3->setColor(0xffffff);
  sunGlow3->setAlpha(.3f);
  sunGlow3->translate(new MyPoint({0, 100}));

  MyCircle *sunGlow2 = new MyCircle(100, 100);
  // sunGlow2->setColor(0xdef2fc);
  sunGlow2->setColor(0xffffff);
  sunGlow2->setAlpha(.4f);
  sunGlow2->translate(new MyPoint({0, 100}));

  MyCircle *sunGlow1 = new MyCircle(80, 80);
  // sunGlow1->setColor(0xf0f9fe);
  sunGlow1->setColor(0xffffff);
  sunGlow1->setAlpha(.5f);
  sunGlow1->translate(new MyPoint({0, 100}));

  MyCircle *sunCenter = new MyCircle(70, 70);
  MyPoint *sunPos = new MyPoint({0, 100});
  sunCenter->setColor(0xffffff);
  sunCenter->translate(sunPos);

  MyGroup *sun = new MyGroup();
  sun->add(sunGlow3);
  sun->add(sunGlow2);
  sun->add(sunGlow1);
  sun->add(sunCenter);

  all.add(sun);

  MyEllipse *cloud22 = new MyEllipse(30, 15, 70);
  cloud22->setColor(0xfffffc);
  cloud22->translate(new MyPoint({40, 0}));
  cloud22->embedPosition();

  MyEllipse *cloud21 = new MyEllipse(40, 20, 70);
  cloud21->setColor(0xfffffc);
  cloud21->translate(new MyPoint({0, 10}));
  cloud21->embedPosition();

  MyGroup *cloud2 = new MyGroup();
  MyPoint *cloud2pos = new MyPoint({300, 280});
  cloud2->add(cloud22);
  cloud2->add(cloud21);
  cloud2->translate(cloud2pos);
  cloud2->scale(3.f);
  all.add(cloud2);

  MyTimeline *tl = new MyTimeline();
  scene.add(tl);
  tl->add(new MyAnimation(
      [cloud2, cloud2pos, sunPos](float progress) {
        MyPoint *pos = cloud2pos->copy();
        pos->scale(.9f + .1f * sinf(TAU * progress), sunPos);
        cloud2->setPosition(pos);
      },
      8000));
  tl->loop(true);
  tl->play();

  MyEllipse *cloud12 = new MyEllipse(50, 20, 70);
  cloud12->setColor(0xfffffc);
  cloud12->translate(new MyPoint({-50, 0}));
  cloud12->embedPosition();

  MyEllipse *cloud11 = new MyEllipse(40, 20, 70);
  cloud11->setColor(0xfffffc);
  cloud11->translate(new MyPoint({0, 10}));
  cloud12->embedPosition();

  MyGroup *cloud1 = new MyGroup();
  MyPoint *cloud1pos = new MyPoint({-320, 240});
  cloud1->add(cloud12);
  cloud1->add(cloud11);
  cloud1->translate(cloud1pos);
  cloud1->scale(3.f);
  all.add(cloud1);

  tl = new MyTimeline();
  scene.add(tl);
  tl->add(new MyAnimation(
      [cloud1, cloud1pos, sunPos](float progress) {
        MyPoint *pos = cloud1pos->copy();
        pos->scale(.9f + .1f * sinf(TAU * progress), sunPos);
        cloud1->setPosition(pos);
      },
      8000));
  tl->loop(true);
  tl->play();

  MyRectangle *grass = new MyRectangle(displayWidth, 100 + halfDisplayHeight);
  grass->setColor(0x67754c);
  grass->translate(new MyPoint({0, -.5f * (float)(-100 + halfDisplayHeight)}));
  all.add(grass);

  std::vector<MyGroup *> sunFlowerRows;
  int m = 12, n = 80;
  for (int i = 0; i < m; i++) {
    MyGroup *row = new MyGroup();
    sunFlowerRows.push_back(row);
    float r = MySunFlower::RADIUS;
    float scl = displayWidth / (2 * r) / n * 8;
    float rowScale = .1f + .9f * powf((float)(i + 1) / (float)m, .7f);
    float sfScale = scl * rowScale;

    for (int j = 0; j < n; j++) {
      // std::cout << rowScale * scl << " ";
      float x = scl * 2 * r * (n / 2 - j) * rowScale;
      float y =
          100.f -
          powf((float)i / (float)(m - 1), 2.f) * (halfDisplayHeight + 100.f);
      if (x < -halfDisplayWidth - sfScale * r ||
          x > halfDisplayWidth + sfScale * r ||
          y < -halfDisplayHeight - sfScale * r ||
          y > halfDisplayHeight + sfScale * r) {
        continue;
      }
      MySunFlower *sunFlower =
          new MySunFlower{0, TAU * (i + j) / (m + n), new MyPoint({x, y})};
      row->add(sunFlower);
      MyTimeline *tl = new MyTimeline();
      scene.add(tl);
      // wait
      tl->add(new MyAnimation(
          [](float progress) {},
          (int)(powf(abs((float)j - .5f * n) / (.5f * n), 1.5f) * 20000.f +
                powf((float)i / (float)m, 2.f) * 6000.f)));
      // animation
      tl->add(new MyAnimation(
          [sunFlower, sfScale](float progress) {
            float factor;
            float thresh = .7f;
            float expand = .3f;
            if (progress < thresh) {
              factor = (1.f + expand) * powf(progress / thresh, .5f);
            } else {
              factor = (1.f + expand) -
                       expand * powf((progress - thresh) / (1 - thresh), 2.f);
            }
            sunFlower->setScale(sfScale * factor);
          },
          400));
      // wait
      tl->add(new MyAnimation([](float progress) {}, 5000));
      // animation
      int choice = std::rand() % 8;
      if (choice == 0) {
        int dir = std::rand() % 2 == 0 ? 1 : -1;
        tl->add(new MyAnimation(
            [sunFlower, sfScale, x, y, dir](float progress) {
              float factor;
              float jump = sfScale * 300.f;
              float _x = x;
              float _y = y;
              float _angle = 0;
              if (progress < .2f) {
                _y = y + jump * powf(progress / .2f, .2f);
              } else if (progress < .8f) {
                _y = y + jump;
                float _progress = (progress - .2f) / .6f;
                float __progress = PI * _progress;
                // integral of sin^2
                _angle = dir * (2.f * __progress - sinf(2.f * __progress));
              } else {
                _y = y + jump * (1.f - powf((progress - .8f) / .2f, 5.f));
              }
              sunFlower->setPosition(new MyPoint({_x, _y}));
              sunFlower->setAngle(_angle);
            },
            1000));
      } else {
        tl->add(new MyAnimation(
            [sunFlower, sfScale](float progress) {
              float factor;
              float thresh = .5f;
              float expand = .2f;
              if (progress < thresh) {
                factor = 1.f + expand * powf(progress / thresh, .5f);
              } else {
                factor = (1.f + expand) -
                         expand * powf((progress - thresh) / (1 - thresh), 2.f);
              }
              sunFlower->setScale(sfScale * factor);
            },
            200));
      }
      tl->setRepeatFrame(2);
      tl->loop(true);
      tl->play();
    }
    all.add(row);
  }

  MyRectangle *darkness = new MyRectangle(displayWidth, displayHeight);
  darkness->setColor(0x000000);
  darkness->setAlpha(.5f);
  all.add(darkness);

  MyTimeline *tl2 = new MyTimeline();
  scene.add(tl2);
  tl2->play();

  tl2->add(new MyAnimation(
      [sun, darkness](float progress) {
        sun->setScale(1.5f * progress);
        darkness->setAlpha(.5f - .5f * progress);
      },
      5000));

  tl2->loop(true);
  tl2->setRepeatFrame(1); // start at 0
  tl2->add(new MyAnimation(
      [sun](float progress) {
        sun->setScale(1.5f + .2f * sinf(TAU * progress));
      },
      10000));

  lastTime = currentTime = glutGet(GLUT_ELAPSED_TIME);
}

void draw() {
  currentTime = glutGet(GLUT_ELAPSED_TIME);
  int deltaTime = currentTime - lastTime;
  lastTime = currentTime;

  scene.update(deltaTime);

  all.draw();
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
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  init();
  glutDisplayFunc(display);
  glutIdleFunc(redisplay);
  glutMainLoop();
  return 0;
}
