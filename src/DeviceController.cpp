#include <GL/glut.h>
#include <stdio.h>



void reshape(int width,int height)
{
  GLfloat aspect;

  if (height == 0)
    height = 1;

  aspect = (GLfloat)width / (GLfloat)height;

  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (width >= height)
    gluOrtho2D(-10.0 * aspect, 10.0 * aspect, -10.0, 10.0);
  else
    gluOrtho2D(-10.0, 10.0, -10.0 / aspect, 10.0 / aspect);

}

void idle(){

  glutPostRedisplay();

}

void mouse(int button, int state, int x, int y)
{

  switch (button) {
  case GLUT_LEFT_BUTTON:
    //   if (state == GLUT_DOWN)
    //       glutIdleFunc(spinDisplay);
    state++;
    break;

  case GLUT_MIDDLE_BUTTON:
   break;

  default: break;
 }

}

void keyboard(unsigned char k, int x, int y)
{
  switch (k) {
  case 27:   // Escape
    exit(0);
    break;
  case 'q': // Quit
    exit(0);
    break;
  case 32: // Spacebar
    printf("KEY: SPACE\n");
    break;
  default:
    return;
  }

}

void specialKeyboard(int key, int x, int y)
{

  switch (key) {
  case GLUT_KEY_RIGHT:
    printf("Key: RIGHT\n");
    break;
  case GLUT_KEY_LEFT:
    printf("Key: LEFT\n");
    break;
  case GLUT_KEY_UP:
    printf("Key: UP\n");
    break;
  case GLUT_KEY_DOWN:
    printf("Key: DOWN\n");
    break;
  default: break;

  }

}

/*
void specialKeys(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_F1:    // F1: Toggle between full-screen and windowed mode
    fullScreenMode = !fullScreenMode;         // Toggle state
    if (fullScreenMode) {                     // Full-screen mode
      windowPosX   = glutGet(GLUT_WINDOW_X); // Save parameters for restoring later
      windowPosY   = glutGet(GLUT_WINDOW_Y);
      windowWidth  = glutGet(GLUT_WINDOW_WIDTH);
      windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
      glutFullScreen();                      // Switch into full screen
    } else {                                         // Windowed mode
      glutReshapeWindow(windowWidth, windowHeight); // Switch into windowed mode
      glutPositionWindow(windowPosX, windowPosX);   // Position top-left corner
    }
    break;
  case GLUT_KEY_RIGHT:    // Right: increase x speed
    xSpeed *= 1.05f; break;
  case GLUT_KEY_LEFT:     // Left: decrease x speed
    xSpeed *= 0.95f; break;
  case GLUT_KEY_UP:       // Up: increase y speed
    ySpeed *= 1.05f; break;
  case GLUT_KEY_DOWN:     // Down: decrease y speed
    ySpeed *= 0.95f; break;
  case GLUT_KEY_PAGE_UP:  // Page-Up: increase ball's radius
    ballRadius *= 1.05f;
    ballXMin = clipAreaXLeft + ballRadius;
    ballXMax = clipAreaXRight - ballRadius;
    ballYMin = clipAreaYBottom + ballRadius;
    ballYMax = clipAreaYTop - ballRadius;
    break;
  case GLUT_KEY_PAGE_DOWN: // Page-Down: decrease ball's radius
    ballRadius *= 0.95f;
    ballXMin = clipAreaXLeft + ballRadius;
    ballXMax = clipAreaXRight - ballRadius;
    ballYMin = clipAreaYBottom + ballRadius;
    ballYMax = clipAreaYTop - ballRadius;
    break;
  }
}
*/
