#ifndef BASEUNIT_H
#define BASEUNIT_H

typedef struct _BaseUnit {
	float x;
	float y;
	int hp;
	int mp;
	int type_bomb; //The type of the bomb
	int type;
	float speed;
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

typedef struct _BaseSword {
	float x;
	float wx;
	float y;
	float wy;
	float sdig;
	float wsdig;
	float gdig;
	float wgdig;
	int flame;
	int wflame;
	char l_or_r;
	int pattern;
	bool flag;
}BaseSword;


void stage_Initialize();

//“®‚«‚ğŒvZ‚·‚é
void stage_Update();

//•`‰æ‚·‚é
void stage_Draw();

//I—¹ˆ—‚ğ‚·‚é
void stage_Finalize();


#endif 