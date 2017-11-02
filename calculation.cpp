#include <math.h>
#include "BaseUnit.h"
#include "BaseEnemy.h"
#include "calculation.h"
#include <time.h>
#include <stdlib.h>
#define PI 3.14159265358979323846
//‰~üã‚ğ‰ñ‚é“®‚«‚ğ‰‰Z‚·‚éŠÖ”
//r=‰~‚Ì”¼Œa
//deg=•`‰æˆê‰ñ‚É‘Î‚·‚éŠp“x
Enemy_status circumference(Enemy_status enemy,float r,float deg, float Ox, float Oy) {
	float rad;
	rad = to_rad(deg);
	enemy.x = r*cos(rad) + Ox;
	enemy.y = r*sin(rad) + Oy;

	return enemy;
}

float Argument_angle(float x1, float y1, float x2, float y2) {
	float dif_x, dif_y, rad;

	dif_x = x2 - x1;
	dif_y = y2 - y1;

	rad = atan2f(dif_y, dif_x);

	return rad;
}

float to_deg(float rad) {
	float deg;

	deg = rad * 180 / PI;
	return deg;
}

float to_rad(float deg) {
	float rad;

	rad = (PI / 180.0)*deg;
	return rad;
}

float number_of_frames(Enemy_status enemy,float x1, float y1, float x2, float y2) {
	float n_of_f;
	float dif_x, dif_y,rad,frame;

	dif_x = x2 - x1;
	dif_y = y2 - y1;

	rad=atan2f(dif_y, dif_x);

	frame = dif_x / (enemy.speed*cos(rad));
	if (frame <= 0) {
		frame = dif_y / (enemy.speed*sin(rad));

	}

	return frame;
}

float sdig_to_gdig(float sdig, float gdig, int flame){
	float dif_rad, srad, grad, rpf;
	srad = to_rad(sdig);
	grad = to_rad(gdig);
	//dif_dig=
	return srad;
}

double urandom() {
	
	return (double)rand() / ((double)RAND_MAX+1.0);
}

int nrandom(int n) {
	return (int)((double)n*urandom());
}
