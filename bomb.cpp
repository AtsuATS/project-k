#include "player.h"
#include "bomb.h"
#include "grobal.h"
	
//static float r; //static�����Ǝ����I�ɏ����l0
float r;

void bomb2(int flag) {
	if (flag == 1 && countflame > 0)
		countflame--;
	if (flag == 2) {
		countflame += 0.5;
		if (countflame == 900) {
			bombflag[0] = 0;
		}
	}
	if (countflame == 0) {
		bombmagnification = 1;
		bombflag[0] = 2;
	}
}

void bomb3(void) {

	if (bombflag[1] == 1) {
		r += 1.43; //���7�b��ɏ����܂�

		if (r > 600) {  //������ύX�����ꍇ��2�s���r�̑����l���ύX�����邱��
			r = 0;
			bombflag[1] = 0;
		}
	}
}

void bomb_Update(void) {
	bomb2(bombflag[0]);
	bomb3();
}

void bomb_Draw(void) {
	DrawCircle(bombflag[2], bombflag[3], r, GetColor(255,255,255), 0, 1);
}