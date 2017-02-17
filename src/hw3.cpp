#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "my/animation.hpp"
#include "my/apple.hpp"
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
int mouseX;
int mouseY;
bool mouseLeftDown = false;
bool mouseRightDown = false;
float mouseViewX;
float mouseViewY;
auto mousePos = new MyPoint({mouseViewX, mouseViewY});

auto apple = new MyApple();
float appleScl = 0.3f;
float appleRadius = MyApple::RADIUS * appleScl;
bool appleDragging = false;
auto man = new MyMan();
auto manHappyTimeline = new MyTimeline();

void init(void) {
  std::srand(std::time(0));

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  // glClearColor(0.2, 0.2, 0.3, 1.0);
  glClearColor(1, 1, 1, 1);

  float x = -halfDisplayWidth + (float)(std::rand() % displayWidth);
  float y = -halfDisplayHeight + (float)(std::rand() % displayHeight);
  // float scl = 0.5f + 0.1f * ((float)(std::rand() % 10) / 10.0f);
  float scl = appleScl;
  apple->setPosition(new MyPoint({x, y}));
  apple->setScale(scl);
  all.add(apple);

  man->setPosition(new MyPoint({0, 0}));
  man->arm11->setAngle(TAU / 4.0f);
  man->arm21->setAngle(-TAU / 4.0f);
  all.add(man);

  auto man1 = man;
  float manIdleCycleTime = 1000;
  float manWalkCycleTime = 2000;
  float manMoveCycleTime = 8000;
  auto man1Idle = [man1](float progress) {

  };
  auto man1Walk = [man1](float progress) {
    float t = progress;
    man1->leg11->setAngle(PI * (2.0f + 0.5f * sinf(t * TAU)));
    man1->leg12->setAngle(PI * (1.8f + 0.7f * sinf(t * TAU)));
    man1->leg21->setAngle(PI * (2.0f + 0.5f * sinf((0.5f + t) * TAU)));
    man1->leg22->setAngle(PI * (1.8f + 0.7f * sinf((0.5f + t) * TAU)));
  };
  auto man1Move = [man1](float progress) {
    man1->setPosition(new MyPoint(
        {displayWidth * (1.2f * progress - 0.1f) - halfDisplayWidth, 0}));
    //  50.0f * std::abs(sinf(t * TAU))}));
  };

  auto tl = new MyTimeline();
  tl->loop(true);
  tl->play();
  tl->add(new MyAnimation(man1Walk, manWalkCycleTime));
  scene.add(tl);

  auto apple1 = apple;
  manHappyTimeline = new MyTimeline();
  manHappyTimeline->add(new MyAnimation(
      [man1, manHappyTimeline, &appleDragging, apple1](float progress) {
        if (appleDragging) {
          return;
        }
        auto applePos = apple1->getPosition();
        auto destPos =
            man1->getPosition()->add(new MyPoint({0, 65 + MyMan::BODY_LENGTH}));
        auto destFromApple = destPos->copy()->sub(applePos);
        applePos->scale(0.9f, destPos);
        float distance = sqrt(destFromApple->copy()->pow(2)->sum());
        // std::cout << distance << std::endl;
        // if (distance > 8.0f) {
          apple1->setPosition(applePos);
        // }
        // float angleToDest =
        //     std::atan2(destFromApple->at(1), destFromApple->at(0));
        // float moveDistance = moveSpeed / (float)frameRate;
        // apple1->translate(new MyPoint({moveDistance * cosf(angleToDest),
        //                                moveDistance * sinf(angleToDest)}));
      },
      400));
  manHappyTimeline->add(new MyAnimation(
      [man1, manHappyTimeline, &appleDragging, apple1](float progress) {
        if (appleDragging) {
          return;
        }
        auto applePos = apple1->getPosition();
        auto destPos =
            man1->getPosition()->add(new MyPoint({0, 45 + MyMan::BODY_LENGTH}));
        auto destFromApple = destPos->copy()->sub(applePos);
        applePos->scale(0.9f, destPos);
        float distance = sqrt(destFromApple->copy()->pow(2)->sum());
        // std::cout << distance << std::endl;
        // if (distance > 8.0f) {
          apple1->setPosition(applePos);
        // }
        // float angleToDest =
        //     std::atan2(destFromApple->at(1), destFromApple->at(0));
        // float moveDistance = moveSpeed / (float)frameRate;
        // apple1->translate(new MyPoint({moveDistance * cosf(angleToDest),
        //                                moveDistance * sinf(angleToDest)}));
      },
      400));
  manHappyTimeline->loop(true);
  // manHappyTimeline->setRepeatFrame(1);
  scene.add(manHappyTimeline);

  // tl = new MyTimeline();
  // tl->loop(true);
  // tl->play();
  // tl->add(new MyAnimation(man1Move, manMoveCycleTime));
  // scene.add(tl);

  lastTime = currentTime = glutGet(GLUT_ELAPSED_TIME);
  elapsedTime = 0;

  all.useDrawLimit(false);
  scene.play();
  manHappyTimeline->stop();
  // scene.stop();
}

float sqr(float x) { return x * x; }

void ik2(MyGroup *leg1, MyGroup *leg2, float len1, float len2, float x,
         float y) {
  auto legPos = leg1->getPosition();
  float localX = x - legPos->at(0);
  float localY = y - legPos->at(1);
  float maxLegLen = len1 + len2;
  float L = std::min(maxLegLen, (float)sqrt(sqr(localX) + sqr(localY)));
  float legAngle = std::atan2(localY, localX);
  float cos1 = (sqr(len1) + sqr(L) - sqr(len2)) / (2.0f * len1 * L);
  float sin1 = sqrt(1.0f - sqr(cos1));
  float leg1Angle = TAU / 4.0f + legAngle - std::atan2(sin1, cos1);
  float cos2 = (sqr(len1) + sqr(len2) - sqr(L)) / (2.0f * len1 * len2);
  float sin2 = sqrt(1.0f - sqr(cos2));
  float leg2Angle = leg1Angle + TAU / 2.0f - std::atan2(sin2, cos2);
  leg1->setAngle(leg1Angle);
  leg2->setAngle(leg2Angle);
}

void updateApple() {
  if (appleDragging) {
    apple->setPosition(mousePos);
  }
}

void updateMan() {
  // if (mouseLeftDown) {
  //   ik2(man->arm21, man->arm22, 0.5f * MyMan::ARM_LENGTH,
  //       0.5f * MyMan::ARM_LENGTH, mouseViewX, mouseViewY);
  // }
  // if (mouseRightDown) {
  //   ik2(man->arm11, man->arm12, 0.5f * MyMan::ARM_LENGTH,
  //       0.5f * MyMan::ARM_LENGTH, mouseViewX, mouseViewY);
  // }
  auto applePos = apple->getPosition();
  float appleX = applePos->at(0);
  float appleY = applePos->at(1);
  ik2(man->arm21, man->arm22, 0.5f * MyMan::ARM_LENGTH,
      0.5f * MyMan::ARM_LENGTH, appleX, appleY);
  ik2(man->arm11, man->arm12, 0.5f * MyMan::ARM_LENGTH,
      0.5f * MyMan::ARM_LENGTH, appleX, appleY);
  auto applePosFromMan = applePos->sub(man->arm21->getPosition());
  float appleFromMan = sqrt(applePosFromMan->copy()->pow(2)->sum());
  if (appleFromMan > MyMan::ARM_LENGTH) {
    float angleToApple =
        std::atan2(applePosFromMan->at(1), applePosFromMan->at(0));
    float moveSpeed = 200; // 100px per sec
    float moveDistance = moveSpeed / (float)frameRate;
    man->translate(new MyPoint({moveDistance * cosf(angleToApple),
                                moveDistance * sinf(angleToApple)}));
  } else {
    manHappyTimeline->play();
  }
}

void update() {
  currentTime = glutGet(GLUT_ELAPSED_TIME);
  int deltaTime = currentTime - lastTime;
  lastTime = currentTime;

  elapsedTime += deltaTime;
  elapsedTime2 += deltaTime;
  if (elapsedTime >= frameTime) {
    scene.update(elapsedTime);
    updateApple();
    updateMan();
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

void onMouseMove(int x, int y) {
  mouseX = x;
  mouseY = y;
  mouseViewX = (float)mouseX - halfDisplayWidth;
  mouseViewY = -(float)mouseY + halfDisplayHeight;
  mousePos->assign({mouseViewX, mouseViewY});
}

void onMouseButton(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      mouseLeftDown = true;
      float appleFromMouse =
          sqrt(apple->getPosition()->sub(mousePos)->pow(2)->sum());
      if (appleFromMouse < appleRadius) {
        appleDragging = true;
      }
      // scene.toggle();
    }
    if (state == GLUT_UP) {
      mouseLeftDown = false;
      appleDragging = false;
      manHappyTimeline->go(0);
      manHappyTimeline->restart();
      manHappyTimeline->stop();
    }
  }
  if (button == GLUT_RIGHT_BUTTON) {
    if (state == GLUT_DOWN) {
      mouseRightDown = true;
    }
    if (state == GLUT_UP) {
      mouseRightDown = false;
    }
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
  glutMouseFunc(onMouseButton);
  glutMotionFunc(onMouseMove);
  glutPassiveMotionFunc(onMouseMove);
  glutMainLoop();
  return 0;
}
