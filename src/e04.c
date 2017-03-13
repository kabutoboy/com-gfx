#include <GL/glut.h> 
#include <math.h>

#define PI 3.14159265358979323846
#define PI2 PI*2

double sphereX(float r, float normtheta, float normphi) {
  return r * cos(normtheta * PI) * sin(normphi * PI2);
}
double sphereY(float r, float normtheta, float normphi) {
  return r * sin(normtheta * PI) * sin(normphi * PI2);
}
double sphereZ(float r, float normtheta, float normphi) {
  return r * cos(normphi * PI2);
}

float c = 5;
float s = 0;
float t = 0;
float ds = 0.0005;
float dt = 0.001;

void display(void)
{

  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);  
  glLoadIdentity();
  gluLookAt(
      c * cos(s) * sin(t),
      c * sin(s) * sin(t),
      c * cos(t),
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
      0.0);  
  t += dt;
  s += ds;
  
  glColor3d(1.0,1.0,1.0);
  int m = 20;
  int n = 40;
  float m_inv = 1.0 / m;
  float n_inv = 1.0 / n;
  float r = 3;
      glBegin(GL_LINES);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      float i0 = i * m_inv;
      float j0 = j * n_inv;
      float i1 = (i+1) * m_inv;
      float j1 = (j+1) * n_inv;
      GLdouble face[][3] = {
        {
          sphereX(r, i0, j0),
          sphereY(r, i0, j0),
          sphereZ(r, i0, j0)
        },
        {
          sphereX(r, i1, j0),
          sphereY(r, i1, j0),
          sphereZ(r, i1, j0)
        },
        {
          sphereX(r, i1, j1),
          sphereY(r, i1, j1),
          sphereZ(r, i1, j1)
        },
        {
          sphereX(r, i0, j1),
          sphereY(r, i0, j1),
          sphereZ(r, i0, j1)
        },
        {
          sphereX(r, i0, j0),
          sphereY(r, i0, j0),
          sphereZ(r, i0, j0)
        }};
      for (int k = 0; k < 5; k++){
        glVertex3dv(face[k]);
      }
    }
  }
      glEnd();
  glFlush();

}

void init()
{

  glClearColor (0.0, 0.0, 0.0, 0.0); 

}

void reshape(int w,int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glFrustum(-2.0,2.0,-2.0,2.0,2.0,10.0);
}

void idle() {
  glutPostRedisplay();
}

int main(int argc, char** argv)
{

  glutInit(&argc,argv); 
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  
  glutInitWindowSize(500,500);
  glutInitWindowPosition(0,0); 
  glutCreateWindow("simple"); 
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  init();
  glutMainLoop();

}
