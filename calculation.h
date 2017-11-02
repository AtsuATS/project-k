#ifndef CALCULATION_H
#define CALCULATION_H
#include "BaseEnemy.h"

Enemy_status circumference(Enemy_status enemy_circle, float r, float deg, float O_x, float O_y);
float Argument_angle(float x1, float y1, float x2, float y2);
float to_deg(float rad);
float to_rad(float deg);
float number_of_frames(Enemy_status enemy, float x1, float y1, float x2, float y2);
float sdig_to_gdig(float sdig, float gdig, int flame);
double urandom();
int nrandom(int);

#endif 
