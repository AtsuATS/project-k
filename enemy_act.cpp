#include "DxLib.h"
#include "grobal.h"
#include "enemy.h"
#include "enemyshot.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "calculation.h"

//act[]�̏�������Y��Ȃ�����

//����deg�̕�����enemy->speed�Ői��
void enemy_act0(Enemy_status *enemy, float deg) {

	float sine, cosine;

	cosine = cos(to_rad(deg));
	sine = sin(to_rad(deg));

	enemy->x += enemy->speed*cosine;
	enemy->y += enemy->speed*sine;

	return;
}

//�v���[���[�̕����ɓ����ŏ��̈�R�}�ŕ���������
void enemy_act1(Enemy_status *enemy) {
	if (enemy->act[1] == 0) {
		enemy->deg = to_deg(atan2f(enemy->y - player.y, enemy->x - player.x))+180;
		enemy->act[1] = 1;
		enemy_act0(enemy, enemy->deg);
	}

	enemy_act0(enemy,enemy->deg);

	return;
}

//�����猻��Ē��S�ŉ�������1��]�̂��ɉE�ɏ�����
//�V���Ɉ�����݂���Ή�]�̕������w��\

void enemy_act2(Enemy_status *enemy) {
	if (enemy->act[2]==0) {
			enemy->x += enemy->speed;
			if (enemy->x >= 275) {
				enemy->deg =0;
				enemy->act[2] = 1;
			}
	}
	else if (enemy->act[2] == 1) {
		if (enemy->deg < 360) {
			enemy_act0(enemy, enemy->deg);
			enemy->deg+=5;
		}
		else {
			enemy->x += enemy->speed;
		}
	}
	return;
}

//�����猻���(���̏ꍇ��)y���W100��؂������_�ŉ�]�A���ɏ�����B
//������݂���ΐ܂�Ԃ��̍��W��A�������w��\�ɂȂ�
void enemy_act3(Enemy_status *enemy, char c) {
	if (enemy->act[3] == 0) {
		enemy->y -= enemy->speed;
		if (enemy->y < 100) {
			if (c == 'l') enemy->deg = 270;
			if (c == 'r') enemy->deg = -90;

			enemy->act[3] = 1;
		}
	}
	else if (enemy->act[3] == 1 && c == 'l') {
		if (enemy->deg > 90) {
			enemy_act0(enemy, enemy->deg);
			enemy->deg -= 4;
		}
		else {
			enemy->y += enemy->speed;
		}
	}
	else if (enemy->act[3] == 1 && c == 'r') {
		if (enemy->deg < 90) {
			enemy_act0(enemy, enemy->deg);
			enemy->deg += 4;
		}
		else {
			enemy->y += enemy->speed;
		}
	}
	return;
}


//���˂���(���Ǘ\��)
void enemy_act4(Enemy_status *enemy) {
	if (enemy->act[4] == 0) {
		enemy_act0(enemy, enemy->deg);
		enemy->deg += 5;
		if (enemy->deg >= 180){
			enemy->act[4] = 1;
		}
	}
	else if (enemy->act[4] == 1) {
		enemy_act0(enemy, enemy->deg);
		enemy->deg -= 5;
		if (enemy->deg <= 0) {
			enemy->act[4] = 0;
		}
	}
	return;
}

//�~�܂�
void enemy_act5(Enemy_status *enemy) {
	if (enemy->act[5] == 0) {
		enemy->y += enemy->speed;
		if (enemy->y >= 200)enemy->act[5] = 1;
	}
	return;
}