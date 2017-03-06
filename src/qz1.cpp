#include <iostream>
#include <vector>
#include <GL/glut.h>

int displayWidth = 1200;
int displayHeight = 600;
float halfDisplayWidth = 0.5f * (float)displayWidth;
float halfDisplayHeight = 0.5f * (float)displayHeight;

std::vector<std::vector<double>> Q = {
  {-1.41400,  -0.81600,   3.65950,   5.77300},
  { 0.00000,  -1.63200,   1.92850,   4.61900},
  { 0.00000,   0.00000,   0.19750,   3.46500},
  {-1.41400,   0.81600,   1.92850,   4.61900},
  { 0.00000,   0.00000,   5.39050,   6.92700},
  { 1.41400,  -0.81600,   3.65950,   5.77300},
  { 1.41400,   0.81600,   1.92850,   4.61900},
  { 0.00000,   1.63200,   3.65950,   5.77300}
};

void init(void) {

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glClearColor(0.2, 0.2, 0.3, 1.0);
  // gluOrtho2D(-halfDisplayWidth, halfDisplayWidth, -halfDisplayHeight,
  //            halfDisplayHeight);

}

void drawQ(std::initializer_list<int> I) {
  glBegin(GL_LINE_LOOP);
  for (auto &i : I) {
    auto &q = Q[i - 1];
    float x = (float)(q[0] / q[3]);
    float y = (float)(q[1] / q[3]);
    x *= displayHeight;
    y *= displayHeight;
    // std::cout << "qlVertex2f(" << x << ", " << y << ")" << std::endl;
    glVertex2f(x, y);
  }
  glEnd();
}

void draw() {
  drawQ({1, 2, 3, 4});
  drawQ({5, 6, 7, 8});
  drawQ({2, 6, 7, 3});
  drawQ({3, 7, 8, 4});
  drawQ({4, 8, 5, 1});
  drawQ({1, 5, 6, 2});
}

void onReshape(int width,int height)
{
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
  draw();
  glFlush();
  glutSwapBuffers();
}

void onRedisplay() { glutPostRedisplay(); }

void onMouse(int button, int state, int x, int y) {
  switch (button) {
  case GLUT_LEFT_BUTTON:
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
  glutReshapeFunc(onReshape);
  glutIdleFunc(onRedisplay);
  glutMouseFunc(onMouse);
  glutMainLoop();
  return 0;
}
