#include <GL/glut.h>
#include <stdio.h>
#include <windows.h>

static float dx1 = 0.0, dy1 = 0.0;
static float dx2 = 0.0, dy2 = 0.0;

float speed = 0.001;

int fps = 0;
int currentTime = 0;
int lastTime = 0;
float elapsedTime = 0;
float deltaTime = 0;

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  currentTime = glutGet(GLUT_ELAPSED_TIME);
  deltaTime = (currentTime - lastTime) / 1000.0;
  elapsedTime += deltaTime;
  lastTime = currentTime;

  // printf("elapsedTime = %5.2f\n", elapsedTime);

  fps++;

  if (elapsedTime >= 1.0) {
    printf("FPS: %d\n", fps);
    elapsedTime = 0.0;
    fps = 0;
  }

  dx1 += speed;

  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(-10.0 + dx1, -10.0 + dy1);
  glVertex2f(-10.0 + dx1, 10.0 + dy1);
  glVertex2f(10.0 + dx1, 10.0 + dy1);
  glVertex2f(10.0 + dx1, -10.0 + dy1);
  glEnd();

  glFlush();
  glutSwapBuffers(); // Swap the buffers.
}

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  gluOrtho2D(-100, 100.0, -100.0, 100.0);

  lastTime = glutGet(GLUT_ELAPSED_TIME);
}

void spinDisplay(void) { glutPostRedisplay(); }

void mouse(int button, int state, int x, int y) {
  int i;

  switch (button) {
  case GLUT_LEFT_BUTTON:

    if (state == GLUT_DOWN) {
      //  for(i = 1; i <= 10;i++){
      glutIdleFunc(spinDisplay);
    }

    //  }
    break;

  case GLUT_MIDDLE_BUTTON:
  default:
    break;
  }
}

void key(unsigned char k, int x, int y) {
  switch (k) {
  case 27: /* Escape */
    exit(0);
    break;

  default:
    return;
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutKeyboardFunc(key);
  glutMainLoop();

  return (0);
}
