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
  glClearColor(0.2, 0.2, 0.3, 1.0);
  // gluOrtho2D(-halfDisplayWidth, halfDisplayWidth, -halfDisplayHeight,
  //            halfDisplayHeight);

  auto sky = new MyRectangle(displayWidth, displayHeight);
  sky->setColor(0xafe0f7);
  all.add(sky);

  auto sunGlow3 = new MyCircle(130, 130);
  sunGlow3->setColor(0xffffff);
  sunGlow3->setAlpha(0.3f);
  sunGlow3->translate(new MyPoint({0, 100}));

  auto sunGlow2 = new MyCircle(100, 100);
  sunGlow2->setColor(0xffffff);
  sunGlow2->setAlpha(0.4f);
  sunGlow2->translate(new MyPoint({0, 100}));

  auto sunGlow1 = new MyCircle(80, 80);
  sunGlow1->setColor(0xffffff);
  sunGlow1->setAlpha(0.5f);
  sunGlow1->translate(new MyPoint({0, 100}));

  auto sunCenter = new MyCircle(70, 70);
  MyPoint *sunPos = new MyPoint({0, 100});
  sunCenter->setColor(0xffffff);
  sunCenter->translate(sunPos);

  auto sun = new MyGroup();
  sun->add(sunGlow3);
  sun->add(sunGlow2);
  sun->add(sunGlow1);
  sun->add(sunCenter);
  sun->setScale(0);

  all.add(sun);

  auto cloud22 = new MyEllipse(30, 15, 70);
  cloud22->setColor(0xfffffc);
  cloud22->translate(new MyPoint({40, 0}));
  cloud22->embedPosition();

  auto cloud21 = new MyEllipse(40, 20, 70);
  cloud21->setColor(0xfffffc);
  cloud21->translate(new MyPoint({0, 10}));
  cloud21->embedPosition();

  auto cloud2 = new MyGroup();
  auto cloud2pos = new MyPoint({400, 280});
  cloud2->add(cloud22);
  cloud2->add(cloud21);
  cloud2->translate(cloud2pos);
  cloud2->scale(2.0f);
  all.add(cloud2);

  auto tl = new MyTimeline();
  scene.add(tl);
  tl->add(new MyAnimation(
      [cloud2, cloud2pos, sunPos](float progress) {
        MyPoint *pos = cloud2pos->copy();
        pos->scale(0.5f + 0.1f * sinf(TAU * progress), sunPos);
        cloud2->setPosition(pos);
      },
      8000));
  tl->loop(true);
  tl->play();

  auto cloud12 = new MyEllipse(50, 20, 70);
  cloud12->setColor(0xfffffc);
  cloud12->translate(new MyPoint({-50, 0}));
  cloud12->embedPosition();

  auto cloud11 = new MyEllipse(40, 20, 70);
  cloud11->setColor(0xfffffc);
  cloud11->translate(new MyPoint({0, 10}));
  cloud12->embedPosition();

  auto cloud1 = new MyGroup();
  auto cloud1pos = new MyPoint({-320, 240});
  cloud1->add(cloud12);
  cloud1->add(cloud11);
  cloud1->translate(cloud1pos);
  cloud1->scale(2.0f);
  all.add(cloud1);

  tl = new MyTimeline();
  scene.add(tl);
  tl->add(new MyAnimation(
      [cloud1, cloud1pos, sunPos](float progress) {
        MyPoint *pos = cloud1pos->copy();
        pos->scale(0.7f + 0.1f * sinf(TAU * progress), sunPos);
        cloud1->setPosition(pos);
      },
      8000));
  tl->loop(true);
  tl->play();

  auto grass = new MyRectangle(displayWidth, 100 + halfDisplayHeight);
  grass->setColor(0x67754c);
  grass->translate(new MyPoint({0, -0.5f * (-100.0f + halfDisplayHeight)}));
  all.add(grass);

  int m = 12;
  int n = 80;
  float r = MySunFlower::RADIUS;
  float d = 2.0f * r;
  float scl = 8.0f * displayWidth / (d * n);
  for (int i = 0; i < m; i++) {
    auto row = new MyGroup();
    row->useDrawLimit(false);
    float rowScale = 0.1f + 0.9f * powf((float)(i + 1) / (float)m, 0.7f);
    float sfScale = scl * rowScale;

    for (int j = 0; j < n; j++) {
      // std::cout << rowScale * scl << " ";
      float x = scl * d * (n / 2 - j) * rowScale;
      float y =
          100.0f -
          powf((float)i / (float)(m - 1), 2.0f) * (halfDisplayHeight + 100.0f);
      if (x < -halfDisplayWidth - sfScale * r ||
          x > halfDisplayWidth + sfScale * r ||
          y < -halfDisplayHeight - sfScale * r ||
          y > halfDisplayHeight + sfScale * r) {
        continue;
      }
      auto sunFlower = new MySunFlower{0, TAU * (float)(i + j) / (float)(m + n),
                                       new MyPoint({x, y})};
      float minRowScale = (0.1f + 0.9f * powf(1.0f / (float)m, 0.7f));
      // normalize
      float scaleColorIntensity =
          1.0f - (sfScale - scl * minRowScale) / (scl * (1.0f - minRowScale));
      // stretch and shift
      scaleColorIntensity = 0.0f + powf(0.6f * scaleColorIntensity, 2.0f);
      sunFlower->scaleColor(0x000000, scaleColorIntensity);
      // std::cout << "scl: " << scl << ", rowScale: " << rowScale
      //           << ", scaleColorIntensity " << scaleColorIntensity << "\n";
      row->add(sunFlower);
      tl = new MyTimeline();
      scene.add(tl);
      // wait
      tl->add(new MyAnimation(
          [](float progress) {},
          (int)(powf(abs((float)j - 0.5f * n) / (0.5f * n), 1.5f) * 20000.0f +
                powf((float)i / (float)m, 2.0f) * 4000.0f)));
      // animation
      tl->add(new MyAnimation(
          [sunFlower, sfScale](float progress) {
            float factor;
            float thresh = 0.7f;
            float expand = 0.3f;
            if (progress < thresh) {
              factor = (1.0f + expand) * powf(progress / thresh, 0.5f);
            } else {
              factor =
                  (1.0f + expand) -
                  expand * powf((progress - thresh) / (1.0f - thresh), 2.0f);
            }
            sunFlower->setScale(sfScale * factor);
          },
          400));
      // wait
      tl->add(new MyAnimation([](float progress) {}, 5000));
      // animation
      int choice = std::rand() % 16;
      if (choice == 0) {
        int dir = std::rand() % 2 == 0 ? 1 : -1;
        tl->add(new MyAnimation(
            [sunFlower, sfScale, x, y, dir](float progress) {
              float factor;
              float jump = sfScale * 300.0f;
              float _x = x;
              float _y = y;
              float _angle = 0;
              if (progress < 0.2f) {
                float _progress = progress / 0.2f;
                _y += jump * powf(_progress, 0.2f);
              } else if (progress < 0.8f) {
                _y = y + jump;
                // normalize
                float _progress = (progress - 0.2f) / 0.6f;
                // scale
                float __progress = PI * _progress;
                // integral of sin^2
                _angle = dir * (2.0f * __progress - sinf(2.0f * __progress));
              } else {
                float _progress = (progress - 0.8f) / 0.2f;
                _y += jump * (1.0f - powf(_progress, 5.0f));
              }
              sunFlower->setPosition(new MyPoint({_x, _y}));
              sunFlower->setAngle(_angle);
            },
            1000));
      } else if (choice == 1) {
        tl->add(new MyAnimation(
            [sunFlower, sfScale, x, y](float progress) {
              float factor;
              float jump = sfScale * 300.0f;
              float _x = x;
              float _y = y;
              float _drawLimit = 1;
              float _scale = 1;
              if (progress < 0.1f) {
                float _progress = progress / 0.1f;
                _y += jump * powf(_progress, 0.2f);
              } else if (progress < 0.2f) {
                _y += jump;
                float _progress = (progress - 0.1f) / 0.1f;
                _scale = 1.0f - powf(_progress, 0.5f);
              } else if (progress < 0.9f) {
                _y += jump;
                // normalize
                float _progress = (progress - 0.2f) / 0.7f;
                // scale
                float __progress = PI * _progress;
                // integral of sin^2
                _drawLimit =
                    (2.0f * __progress - sinf(2.0f * __progress)) / TAU;
                // _drawLimit = _progress;
              } else {
                float _progress = (progress - 0.9f) / 0.1f;
                _y += jump * (1.0f - powf(_progress, 5.0f));
              }
              sunFlower->setScale(sfScale * _scale);
              sunFlower->setPosition(new MyPoint({_x, _y}));
              sunFlower->limitDraw(_drawLimit);
            },
            2000));
      } else {
        tl->add(new MyAnimation(
            [sunFlower, sfScale](float progress) {
              float factor = 1.0f;
              float thresh = 0.5f;
              float expand = 0.2f;
              if (progress < thresh) {
                factor += expand * powf(progress / thresh, 0.5f);
              } else {
                factor +=
                    expand *
                    (1.0f - powf((progress - thresh) / (1.0f - thresh), 2.0f));
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

  auto darkness = new MyRectangle(displayWidth, displayHeight);
  darkness->setColor(0x000000);
  darkness->setAlpha(0.7f);
  all.add(darkness);

  tl = new MyTimeline();
  scene.add(tl);
  tl->play();

  tl->add(new MyAnimation(
      [sun, darkness](float progress) {
        sun->setScale(1.5f * progress);
        darkness->setAlpha(0.7f - 0.7f * progress);
      },
      5000));

  tl->loop(true);
  tl->setRepeatFrame(1); // start at 0
  tl->add(new MyAnimation(
      [sun](float progress) {
        sun->setScale(1.5f + 0.2f * sinf(TAU * progress));
      },
      10000));

  auto man1 = new MyMan();
  all.add(man1);

  tl = new MyTimeline();
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
  GLfloat aspect;

  if (height == 0)
    height = 1;

  aspect = (GLfloat)width / (GLfloat)height;

  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-halfDisplayWidth, halfDisplayWidth, -halfDisplayHeight,
             halfDisplayHeight);
  // if (width >= height)
  //   gluOrtho2D(-500.0 * aspect, 500.0 * aspect, -500.0, 500.0);
  // else
  //   gluOrtho2D(-500.0, 500.0, -500.0 / aspect, 500.0 / aspect);
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
