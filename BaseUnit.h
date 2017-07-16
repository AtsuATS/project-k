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
	int power;//�ǉ�
	int type;
	int speed;
	bool flag;
}BaseShot;

typedef struct _BaseSword {
	float x;
	float y;
	float sdig;
	float gdig;
	int flame;
	char l_or_r;
	int pattern;
	bool flag;
}BaseSword;


void stage_Initialize();

//�������v�Z����
void stage_Update();

//�`�悷��
void stage_Draw();

//�I������������
void stage_Finalize();


#endif 