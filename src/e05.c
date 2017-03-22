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

const static float ambient[6][4] = {
  { 0.0, 0.0, 0.0, 1.0 }, // Black Plastic
  { 0.329412, 0.223529, 0.027451, 1.0 }, // Brass
  { 0.2125,0.1275,0.054,1.0 }, // Bronze
  { 0.25,0.25,0.25,1.0 }, //Chrome
  { 0.191125,0.0735,0.0225,1.0 }, //Copper
  { 0.24725,0.1995,0.0745,1.0 } //Gold
};
const static float diffuse[6][4] = {
  { 0.01, 0.01, 0.01, 1.0 },
  { 0.780392, 0.568627, 0.113725, 1.0 },
  { 0.714,0.4284,0.18144,1.0 },
  { 0.4,0.4,0.4,1.0 },
  { 0.7038,0.27048,0.0828,1.0 },
  { 0.75164,0.60648,0.22648,1.0 }
};
const static float specular[6][4] = {
  { 0.5, 0.5, 0.5, 1.0 },
  { 0.992157, 0.941176, 0.807843, 1.0 },
  { 0.393548,0.271906,0.166721,1.0 },
  { 0.774597,0.774597,0.774597,1.0 },
  { 0.256777,0.137622,0.086014,1.0 },
  { 0.628281,0.555802,0.366065,1.0 }
};
const static float shininess[6][1] = {
  { 32.0 },
  { 27.8974 },
  { 25.6 },
  { 76.8 },
  { 12.8 },
  { 51.2 }
};
GLfloat light0pos[] = {0, 0, 10, 0};
GLfloat light1pos[] = {0, 0, -10, 0};
GLfloat white[] = {1.0,1.0,1.0,1.0};

float c = 20;
float s = 0;
float t = 0;
float ds = 0;
float dt = 1;
int id;

int frameTime = 1000 / 60;

int signum(int n) {
  if (n < 0) return -1;
  if (n > 0) return 1;
  return 0;
}

void cache() {
  id = glGenLists(1);

  glNewList(id, GL_COMPILE);
  // glColor3d(1.0,1.0,1.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[5]);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[5]);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular[5]);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess[5]);
  int m = 600;
  int n = 16;
  float m_inv = 1.0 / m;
  float n_inv = 1.0 / n;
  float r = 3;
  float dx = 0.1;
  float dy = 0.1;
  float dz = 0.1;
  float ox = 0;
  float oy = 0;
  float oz = 0;
  for (int i = -m; i < m; i++) {
    for (int j = -n; j < n; j++) {
      float i0 = r * i * m_inv;
      float j0 = r * j * n_inv;
      float i1 = r * (i + m / 10) * m_inv;
      float j1 = r * (j + 1) * n_inv;
      glBegin(GL_TRIANGLES);
      GLdouble vertex[][3] = {
        {
          ox + X(i0, j0),
          oy + Y(i0, j0),
          oz + Z(i0, j0)
        },
        {
          ox + X(i1, j0),
          oy + Y(i1, j0),
          oz + Z(i1, j0)
        },
        {
          ox + X(i1, j1),
          oy + Y(i1, j1),
          oz + Z(i1, j1)
        },
        {
          ox + X(i1, j1),
          oy + Y(i1, j1),
          oz + Z(i1, j1)
        },
        {
          ox + X(i0, j1),
          oy + Y(i0, j1),
          oz + Z(i0, j1)
        },
        {
          ox + X(i0, j0),
          oy + Y(i0, j0),
          oz + Z(i0, j0)
        }};
      for (int k = 0; k < 6; k++){
        if (k % 3 == 0) {
          GLdouble a[3] = {
            vertex[k+1][0] - vertex[k][0],
            vertex[k+1][1] - vertex[k][1],
            vertex[k+1][2] - vertex[k][2]
          };
          GLdouble b[3] = {
            vertex[k+2][0] - vertex[k][0],
            vertex[k+2][1] - vertex[k][1],
            vertex[k+2][2] - vertex[k][2]
          };
          GLdouble normal[3] = {
            a[1] * b[2] - a[2] * b[1],
            a[0] * b[2] - a[2] * b[0],
            a[0] * b[1] - a[1] * b[0]
          };
          GLdouble norm = sqrt(
            normal[0] * normal[0] +
            normal[1] * normal[1] +
            normal[2] * normal[2]
          );
          normal[0] /= norm;
          normal[1] /= norm;
          normal[2] /= norm;
          glNormal3dv(normal);
        }
        glVertex3dv(vertex[k]);
      }
      glEnd();
    }
  }
  glEndList();
}

void display(void)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(
      // c * cos(s) * sin(t),
      // c * sin(s) * sin(t),
      // c * cos(t),
      0.0,
      0.0,
      5.0,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
      0.0);
  t += dt;
  s += ds;

  glLightfv(GL_LIGHT0,GL_POSITION,light0pos);
  glLightfv(GL_LIGHT1,GL_POSITION,light1pos);
  glPushMatrix();
  glRotated(t,0.0,1.0,0.0);
  glCallList(id);
  glPopMatrix();
  glFlush();

}

void init()
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,white);
  cache();
}

void reshape(int w,int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(30.0,(double)w/(double)h,1.0,100.0);
  // glFrustum(-3.0,3.0,-3.0,3.0,1.0,100.0);
  // glMatrixMode(GL_MODELVIEW);
}

void idle() {
  glutPostRedisplay();
}

void timer(int value) {
  glutPostRedisplay();
  glutTimerFunc(frameTime, timer, 0);
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
  // glutIdleFunc(idle);
  glutTimerFunc(0, timer, 0);
  init();
  glutMainLoop();

}
