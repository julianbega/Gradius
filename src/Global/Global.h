#ifndef GLOBAL_H
#define GLOBAL_H

extern bool pause;
extern float timer;
extern float groundShootTimer;
extern float groundShootCurve;

bool changeFrame();
void controlPause(bool &pause);

#endif 