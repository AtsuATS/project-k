#ifndef BASEUNIT_H
#define BASEUNIT_H

typedef struct _BaseUnit {
	float x;
	float y;
	int hp;
	int type;
	int speed;
	bool flag;
}BaseUnit;

typedef struct _BaseShot {
	float x;
	float y;
	int power;//’Ç‰Á
	int type;
	int speed;
	bool flag;
}BaseShot;


void stage_Initialize();

//“®‚«‚ğŒvZ‚·‚é
void stage_Update();

//•`‰æ‚·‚é
void stage_Draw();

//I—¹ˆ—‚ğ‚·‚é
void stage_Finalize();


#endif 