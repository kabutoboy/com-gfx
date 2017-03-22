#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/


GLdouble vertex[][3] = {
  {-1.0,-1.0,1.0},
  {1.0,-1.0,1.0},
  {1.0,1.0,1.0},
  {-1.0,1.0,1.0},
  {-1.0,-1.0,-1.0},
  {1.0,-1.0,-1.0},
  {1.0,1.0,-1.0},
  {-1.0,1.0,-1.0}
};

int face[][4] = {
  {0,1,2,3},
  {1,5,6,2},
  {5,4,7,6},
  {4,0,3,7},
  {4,5,1,0},
  {3,2,6,7}
};

GLdouble color[][3] = {
  {1.0,0.0,0.0},
  {0.0,1.0,0.0},
  {0.0,0.0,1.0},
  {1.0,1.0,0.0},
  {1.0,0.0,1.0},
  {0.0,1.0,1.0}
};

GLdouble normal[][3] = {
  {0.0,0.0,1.0},
  {1.0,0.0,0.0},
  {0.0,0.0,-1.0},
  {-1.0,0.0,0.0},
  {0.0,-1.0,0.0},
  {0.0,1.0,0.0}
};


GLfloat light0pos[] = {0.0,3.0,5.0,1.0};
GLfloat light1pos[] = {5.0,3.0,0.0,1.0};

GLfloat green[] = {0.0,1.0,0.0,1.0};

void display(void)
{

  int i,j;
  static int r = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity();
  gluLookAt(3.0,4.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);  
  
  glLightfv(GL_LIGHT0,GL_POSITION,light0pos);
  glLightfv(GL_LIGHT1,GL_POSITION,light1pos);

  glRotated((double)r,0.0,1.0,0.0);
  glBegin(GL_QUADS);
  for(j = 0;j < 6;j++){
    glNormal3dv(normal[j]);
    for(i = 0; i < 4;i++){
      glVertex3dv(vertex[face[j][i]]);
    }
  }
  glEnd();
  glutSwapBuffers();

  if(++r >= 360){
    r = 0;
    glutIdleFunc(0);
  }
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
  glLightfv(GL_LIGHT1,GL_DIFFUSE,green);
}

void reshape(int w,int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0,(double)w/(double)h,1.0,100.0);

  glMatrixMode(GL_MODELVIEW);

}
void idle(void)
{
  glutPostRedisplay();
}

void mouse(int button,int state,int x,int y)
{
  switch(button){
  case GLUT_LEFT_BUTTON:
    if(state == GLUT_UP) glutIdleFunc(idle);
    break;
  case GLUT_MIDDLE_BUTTON:
    if(state == GLUT_UP){
      glutIdleFunc(0);
      glutPostRedisplay();
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if(state == GLUT_UP) exit(0);
    break;
  default:
    break;
  }
}


int main(int argc, char** argv)
{

  glutInit(&argc,argv); 
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);  
  glutInitWindowSize(500,500);
  glutInitWindowPosition(0,0); 
  glutCreateWindow("simple"); 
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  init();
  glutMainLoop();

}
