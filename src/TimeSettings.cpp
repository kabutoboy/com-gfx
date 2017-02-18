#include <stdio.h>
#include <GL/glut.h>
#include "Parameters.hpp"
#include "TimeSettings.hpp"

void StartTime(){

  // currentTime <-- lastTime 

  lastTime = glutGet (GLUT_ELAPSED_TIME);

 
}


float CalculateDeltaTime()
{

  float dt;

  currentTime = glutGet (GLUT_ELAPSED_TIME);
  dt  = (currentTime - lastTime)/1000.0;
  
  return dt;

}

void CalculateFrameRate(float dt)
{

  elapsedTime += dt;
  fps++;

  if(elapsedTime >= 1.0){
    printf("fps = %d\n",fps);
    fps = 0;
    elapsedTime = 0.0f;
  }

  lastTime = currentTime;
}

void Timer(int value) {
  glutPostRedisplay();      
  glutTimerFunc(refreshMills, Timer, 0); 
}



