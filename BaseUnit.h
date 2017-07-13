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


void stage_Initialize();

//�������v�Z����
void stage_Update();

//�`�悷��
void stage_Draw();

//�I������������
void stage_Finalize();


#endif 