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

int edge[][2] = {
  {0,1},
  {1,2},
  {2,3},
  {3,0},
  {4,5},
  {5,6},
  {6,7},
  {7,4},
  {0,4},
  {1,5},
  {2,6},
  {3,7}
};


int face[][4] = {
  {0,1,2,3},
  {1,5,6,2},
  {5,4,7,6},
  {4,0,3,7},
  {4,5,1,0},
  {3,2,6,7}
};

void display(void)
{

  int i,j;

  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(3.0,4.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);  

 glColor3d(1.0,1.0,1.0);



 for(j = 0;j < 6;j++){
    glBegin(GL_LINE_LOOP);
    for(i = 0; i < 4;i++)
      glVertex3dv(vertex[face[j][i]]); 
    glEnd();
 }


  glutSwapBuffers();




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
  //gluPerspective(30.0,(double)w/(double)h,1.0,100.0);
  glFrustum(-2.0,2.0,-2.0,2.0,2.0,10.0);


}


int main(int argc, char** argv)
{

  glutInit(&argc,argv); 
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);  
  glutInitWindowSize(500,500);
  glutInitWindowPosition(0,0); 
  glutCreateWindow("simple"); 
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  init();
  glutMainLoop();

}
