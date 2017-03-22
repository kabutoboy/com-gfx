#include <GL/glut.h> 
#include <math.h>

#define PI 3.14159265358979323846
#define PI2 PI*2

double R(float u, float v) {
  return 0.5 * (exp(u) - exp(u-1.0)) * (1.0 - 0.05 * pow(sin(3000*u), 12));
}
double X(float u, float v) {
  return R(u, v) * cos(v);
}
double Y(float u, float v) {
  return (R(u, v) * sin(v) + 0.5 * (exp(u) + exp(u-1.0))) * sin(360*u);
}
double Z(float u, float v) {
  return (R(u, v) * sin(v) + 0.5 * (exp(u) + exp(u-1.0))) * cos(360*u);
}
double sphereX(float r, float normtheta, float normphi) {
  return r * cos(normtheta * PI) * sin(normphi * PI2);
}
double sphereY(float r, float normtheta, float normphi) {
  return r * sin(normtheta * PI) * sin(normphi * PI2);
}
double sphereZ(float r, float normtheta, float normphi) {
  return r * cos(normphi * PI2);
}

float c = 10;
float s = 0;
float t = 0;
float ds = 0.0005;
float dt = 0.001;
int id;

void cache() {
  id = glGenLists(1);

  glNewList(id, GL_COMPILE);
  glColor3d(1.0,1.0,1.0);
  int m = 200;
  int n = 50;
  float m_inv = 1.0 / m;
  float n_inv = 1.0 / n;
  float r = 4;
  float dx = 0.1;
  float dy = 0.1;
  float dz = 0.1;
  float ox = 0;
  float oy = 0;
  float oz = 5;
  for (int i = -m; i < m; i++) {
    glBegin(GL_LINE_LOOP);
    for (int j = -n; j < n; j++) {
      float i0 = r * i * m_inv;
      float j0 = r * j * n_inv;
      GLdouble face[][3] = {
        {
          ox + X(i0, j0),
          oy + Y(i0, j0),
          oz + Z(i0, j0)
        },
        {
          ox + dx+X(i0, j0),
          oy + dy+Y(i0, j0),
          oz + dz+Z(i0, j0)
        }};
      for (int k = 0; k < 1; k++){
        glVertex3dv(face[k]);
      }
    }
    glEnd();
  }
  glEndList();
}

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
  
  glCallList(id);
  glFlush();

}

void init()
{

  glClearColor (0.0, 0.0, 0.0, 0.0); 
  cache();
}

void reshape(int w,int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glFrustum(-3.0,3.0,-3.0,3.0,2.0,20.0);
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
