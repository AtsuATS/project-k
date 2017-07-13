#include <math.h>
#include "BaseEnemy.h"
#include "calculation.h"
#define R 100

/*�����ړ�
*�n�_(x1,y1)
*�I�_(x2,y2)
*/
void enemy_act0(Enemy_status *enemy, float x1,float y1,float x2,float y2) {

	float A_a, sine, cosine;
	if (enemy->function == 0) {
		enemy->x = x1;
		enemy->y = y1;
		enemy->function = 1;
	}
	A_a = Argument_angle(x1, y1, x2, y2);
	if (x2 - x1 == 0) cosine = 0;
	else cosine = cos(A_a);
	if (y2 - y1 == 0)sine = 0;
	else sine = sin(A_a);
	enemy->x += enemy->speed*cosine;
	enemy->y += enemy->speed*sine;

	return;
}

void enemy_act1(void) {}

void enemy_act2(void) {}

//������E�ւ̈ړ�
void enemy_act3(Enemy_status *enemy) {
	enemy->x += enemy->speed;
	return;
}

//�E���獶�ւ̈ړ�
void enemy_act4(Enemy_status *enemy) {
	enemy->x -= enemy->speed;
	return ;
}

//�����璆���ŉ������Ɉ��]�B�̂��ɉE�֏�����
void enemy_act5(Enemy_status *enemy) {
	static bool c_flag = 0;
	static float deg = -90;
	//circumference(Enemy_status enemy_circle,float r,float deg,float O_x,float O_y):�~�^��
	if ((enemy->x > 275&&deg<=270)||c_flag==1) {
		c_flag = 1;
		*enemy = circumference(*enemy, R, deg,275,300);
		deg++;
		if (deg >= 270) {
			c_flag = 0;
		}
	}
	else
	enemy->x +=2;
	return;
}

//�E���璆���ŉ������Ɉ��]�B�̂��ɍ��֏�����
void enemy_act6(Enemy_status *enemy){
	static bool c_flag = 0;
	static float deg = 270;
	//circumference(Enemy_status enemy_circle,float r,float deg,float O_x,float O_y):�~�^��
	//�����̊֐���enemy,cpp�Ɉړ�����\��
	if ((enemy->x < 275 && deg >= -90) || c_flag == 1) {
		c_flag = 1;
		*enemy = circumference(*enemy, R, deg, 275, 300);
		deg--;
		if (deg <= -90) {
			c_flag = 0;
		}
	}
	else
	enemy->x -= 2;
	return ;
}

/*�n�_���璆�p�_���o�R���I�_�ւ̒����ړ�
*�n�_(x1,y1)�����ʊO����o��
*���p�_1��(x2,y2)�ŕ����]��
*�I�_(x3,y3)�ŉ�ʊO
*/
void enemy_act7(Enemy_status *enemy, float x1, float y1, float x2, float y2, float x3, float y3) {
	/*flag:
	*[0]=���p�_��ʉ߂������ǂ���(0=���ʉ�1=�ʉ�)
	*[1]=�R�}���̌v�Z���������ǂ���(0=���v�Z1=�v�Z�ς�)
	*/
	static bool flag[2] = { 0 };
	static float A_a,frame,sine,cosine,distance_x,distance_y;
	static int frame_times = 0;
	//�n�_���璆�p�_�܂ł̈�R�}������̈ړ�����
	if (flag[0] == 0) {
		if (flag[1] == 0) {
			flag[1] = 1;
			enemy->x = x1;
			enemy->y = y1;	//�ʒu�̏�����
			frame = number_of_frames(*enemy, x1, y1, x2, y2);	//���p�_�܂ł̃t���[�����̌v�Z
			A_a = Argument_angle(x1, y1, x2, y2);
			if (x2 - x1 == 0) cosine = 0;
			else cosine = cos(A_a);
			if (y2 - y1 == 0)sine = 0;
			else sine = sin(A_a);
			distance_x = enemy->speed*cosine;
			distance_y = enemy->speed*sine;
			enemy->x -= distance_x;
			enemy->y -= distance_y;
		}
		enemy->x += distance_x;
		enemy->y += distance_y;

		if(frame_times>frame){
			flag[0] = 1;
			flag[1] = 0;
		}
	}
	//���p�_����I�_�܂ł̈�R�}������̈ړ�����
	else {
		if (flag[1] == 0) {
			flag[1] = 1;
			frame = number_of_frames(*enemy, x2, y2, x3, y3);
			A_a = Argument_angle(x2, y2, x3, y3);
			if (x3 - x2 == 0) cosine = 0;
			else cosine = cos(A_a);
			if (y3 - y2 == 0)sine = 0;
			else sine = sin(A_a);
			distance_x = enemy->speed*cosine;
			distance_y = enemy->speed*sine;
		}
		enemy->x += distance_x;
		enemy->y += distance_y;

		if (frame_times>frame) {
			flag[0] = 1;
			flag[1] = 0;
			frame_times = -1;
		}

	}
	frame_times++;
	return;
}

/*�n�_�����~�_�܂ł̒����ړ�
*����~��̏����͖�����
*�n�_(x1,y1)
*��~�_(x2,y2)
*/
void enemy_act8(Enemy_status *enemy,float x1,float y1,float x2,float y2) {
	/*flag
	*[0]=��~�_�ɓ��B�������ǂ���
	*[1]=�ŏ��̏������������ǂ���
	*/
	static bool flag[2] = { 0 };
	static float frame;
	static float A_a, sine, cosine,distance_x,distance_y;
	static int frame_times=0;
	if (flag[0] == 0) {
		if (flag[1] == 0) {
			flag[1] = 1;
			enemy->x = x1;
			enemy->y = y1;
			frame = number_of_frames(*enemy, x1, y1, x2, y2);
			A_a = Argument_angle(x1, y1, x2, y2);
			if (x2 - x1 == 0) cosine = 0;
			else cosine = cos(A_a);
			if (y2 - y1 == 0)sine = 0;
			else sine = sin(A_a);
			distance_x = enemy->speed*cosine;
			distance_y = enemy->speed*sine;
			enemy->x -= distance_x;
			enemy->y -= distance_y;
		}
		else {
			enemy->x += distance_x;
			enemy->y += distance_y;
		}
		frame_times++;
		if (frame_times > frame) {
			flag[0] = 1;
			frame_times = 0;
		}
	}
	return;
}