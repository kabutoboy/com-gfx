#include <GL/glut.h>   
#include <math.h>
//#include "Bitmap.h"


#define PI 3.141592



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
  {0,1,2,3},  // front
  {1,5,6,2},  // right
  {5,4,7,6},  // back
  {4,0,3,7},  // left
  {4,5,1,0},  // bottom
  {3,2,6,7}   // top
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



GLfloat light0pos[] = {8.0,8.0,2.0,0.0};
GLfloat light0posR[] = {3.0,-8.0,3.0,1.0};


GLfloat light1pos[] = {3.0,3.0,3.0,0.0};
GLfloat light2pos[] = {-3.0,3.0,3.0,0.0};

GLfloat white[] = {1.0,1.0,1.0,5.0};
GLfloat green[] = {0.0,1.0,0.0,5.0};
GLfloat red[] = {1.0,0.0,0.0,0.4};
GLfloat blue[] = {0.0,0.0,1.0,5.0};
GLfloat grey[] = {0.2,0.2,0.2,5.0};
GLfloat shininess[] = {130.0};


double  shadowMatrix[16];
double  shadowMatrix2[16];
float  ground[] = {0.0, 1.0, 0.0, 0.0};
float  ground2[] = {0.7071, 0.7071, 0.0, 0.0};


void Sphere(float radius,int nSlice,int nStack);
void Cube();
void  MakeShadowMatrix(double m[16],float lightPosition[4],float ground[4]);
void drawFloor(double widthX, double widthZ, int nx, int nz);



void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity();
  gluLookAt(10.0,10.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0);  

  glLightfv(GL_LIGHT0,GL_POSITION,light0pos);

  //---------------- Floor ---- 

  glPushMatrix();
  glTranslatef(0.0,-0.01,0.0);
  drawFloor(20.0,20.0,10,10);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-45.0, 0.0, 0.0, 1.0);
  glTranslatef(0.0,-0.01,0.0);
  drawFloor(20.0,20.0,10,10);
  glPopMatrix();

  //-------------- Cube#1 ------------------

  glMaterialfv(GL_FRONT, GL_AMBIENT, green);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
  glMaterialfv(GL_FRONT, GL_SPECULAR, green);
  glMaterialfv(GL_FRONT, GL_SHININESS,shininess);

  
  glPushMatrix();
  glTranslatef(2.0,2.0,0.0);
  glScalef(1.0, 3.0, 1.0);
  Cube();
  glPopMatrix();

  //---------------- Cube#1 's shadow  ---- 

  // Shadow

  glDisable(GL_LIGHTING);

  glPushMatrix();
  glMultMatrixd(shadowMatrix);
  glTranslatef(2.0, 2.0, 0.0);
  glScalef(1.0, 3.0, 1.0);
  glColor3f(0.2, 0.2, 0.2);
  Cube();
  glPopMatrix();

  glPushMatrix();
  glMultMatrixd(shadowMatrix2);
  glTranslatef(2.0, 2.0, 0.0);
  glScalef(1.0, 3.0, 1.0);
  glColor3f(0.2, 0.2, 0.2);
  Cube();
  glPopMatrix();


  glEnable(GL_LIGHTING);


  glutSwapBuffers();

  glFlush();
}

void init()
{

  glClearColor(0.4, 0.4, 0.8, 1.0);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  //--------- Set Light ---------

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  //  glEnable(GL_LIGHT1);
  //  glEnable(GL_LIGHT2);

   glLightfv(GL_LIGHT0,GL_POSITION,light0pos);
  //  glLightfv(GL_LIGHT1,GL_POSITION,light1pos);
  //  glLightfv(GL_LIGHT2,GL_POSITION,light2pos);

  glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
  //  glLightfv(GL_LIGHT1,GL_DIFFUSE,red);
  //  glLightfv(GL_LIGHT2,GL_DIFFUSE,green);

  //--------- Shadow matrix ----

  MakeShadowMatrix(shadowMatrix,light0pos,ground);
  MakeShadowMatrix(shadowMatrix2,light0pos,ground2);

}

void reshape(int w,int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0,(double)w/(double)h,1.0,100.0);

  glMatrixMode(GL_MODELVIEW);

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

  init();
  glutMainLoop();

}


void Sphere(float radius,int nSlice,int nStack){

	int i, j;
	double phi;
	double theta;
	float p[31][31][3];
	float *p1, *p2, *p3, *p4;

	if (nSlice > 30) nSlice = 30;
	if (nStack > 30) nStack = 30;


	for (i = 0;i <= nSlice;i++)
	{
		phi = 2.0 * PI * (double)i / (double)nSlice;
		for (j = 0;j <= nStack;j++)
		{
			theta = PI * (double)j / (double)nStack;
			p[i][j][0] = (float)(radius * sin(theta) * cos(phi));
			p[i][j][1] = (float)(radius * sin(theta) * sin(phi));
			p[i][j][2] = (float)(radius * cos(theta));
		}
	}
	//Top(j=0)
	for (i = 0;i < nSlice; i++)
	{
		p1 = p[i][0];	  p2 = p[i][1];
		p3 = p[i + 1][1];
		glBegin(GL_TRIANGLES);
		glNormal3fv(p1); glVertex3fv(p1);
		glNormal3fv(p2); glVertex3fv(p2);
		glNormal3fv(p3); glVertex3fv(p3);
		glEnd();
	}
	//Bottom
	j = nStack - 1;
	for (i = 0;i < nSlice; i++)
	{
		p1 = p[i][j];	  p2 = p[i][j + 1];
		p3 = p[i + 1][j];
		glBegin(GL_TRIANGLES);
		glNormal3fv(p1); glVertex3fv(p1);
		glNormal3fv(p2); glVertex3fv(p2);
		glNormal3fv(p3); glVertex3fv(p3);
		glEnd();
	}

	for (i = 0;i < nSlice;i++) {
		for (j = 1;j < nStack - 1; j++)
		{
			p1 = p[i][j];	  p2 = p[i][j + 1];
			p3 = p[i + 1][j + 1]; p4 = p[i + 1][j];
			glBegin(GL_QUADS);
			glNormal3fv(p1); glVertex3fv(p1);
			glNormal3fv(p2); glVertex3fv(p2);
			glNormal3fv(p3); glVertex3fv(p3);
			glNormal3fv(p4); glVertex3fv(p4);
			glEnd();
		}

	}
}

void Cube(){
  int i,j;

  glBegin(GL_QUADS);
  for(j = 0;j < 6;j++){
    glNormal3dv(normal[j]);
    for(i = 0; i < 4;i++){
      glVertex3dv(vertex[face[j][i]]);
    }
  }
  glEnd();


}

void MakeShadowMatrix(double m[16], float lightPosition[4], float ground[4])

{

    float dotNL,d;
    float  mat[4][4];
    
    dotNL = ground[0]*lightPosition[0] + ground[1]*lightPosition[1] +  ground[2]*lightPosition[2];
    
    d = ground[3];
    
    m[0] = mat[0][0] = dotNL + d - lightPosition[0] * ground[0];
    m[4] = mat[0][1] = 0.0 - lightPosition[0] * ground[1];
    m[8] = mat[0][2] = 0.0 - lightPosition[0] * ground[2];
    m[12] = mat[0][3] = 0.0 - lightPosition[0] * ground[3]; // ground[3] = d;
    
    m[1] = mat[1][0] = 0.0 - lightPosition[1] * ground[0];
    m[5] = mat[1][1] = dotNL +d  - lightPosition[1] * ground[1];
    m[9] = mat[1][1] = 0.0 - lightPosition[1] * ground[2];
    m[13] = mat[1][3] = 0.0 - lightPosition[1] * ground[3];
    
    m[2] = mat[2][0] = 0.0 - lightPosition[2] * ground[0];
    m[6] = mat[2][1] = 0.0 - lightPosition[2] * ground[1];
    m[10] = mat[2][2] = dotNL +d  - lightPosition[2] * ground[2];
    m[14] = mat[2][3] = 0.0 - lightPosition[2] * ground[3];
    
    m[3] = mat[3][0] = 0.0 -  ground[0];
    m[7] = mat[3][1] = 0.0 - ground[1];
    m[11] = mat[3][2] = 0.0 -  ground[2];
    m[15] = mat[3][3] = dotNL ;
    
}

void drawFloor(double widthX, double widthZ, int nx, int nz)
{
	int i, j;

	double wX = widthX / (double)nx;
	double wZ = widthZ / (double)nz;

	float diffuse[][4   ] = {{ 0.9f, 0.6f, 0.3f, 1.0f },{ 0.3f, 0.5f, 0.8, 1.0f } };
	float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 10);

	glNormal3d(0.0, 1.0, 0.0);
	glPushMatrix();
	glBegin(GL_QUADS);
	for (j = 0; j < nz; j++) {
		double z1 = -widthZ / 2.0 + wZ * j; double z2 = z1 + wZ;
		for (i = 0; i < nx; i++) {
			double x1 = -widthX / 2.0 + wX * i; double x2 = x1 + wX;

			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[(i + j) & 1]);
			glVertex3d(x1, 0.0, z1);
			glVertex3d(x1, 0.0, z2);
			glVertex3d(x2, 0.0, z2);
			glVertex3d(x2, 0.0, z1);
		}
	}
	glEnd();
	glPopMatrix();
}





