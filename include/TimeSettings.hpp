#ifndef TIMESETTINGS_H
#define TIMESETTINGS_H


static int refreshMills;

void StartTime();
float CalculateDeltaTime();
void CalculateFrameRate(float deltaTime);
void Timer(int value);

#endif
