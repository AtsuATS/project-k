#include "DxLib.h"

int key[256]; // �L�[��������Ă���t���[�������i�[����

//�L�[�̓��͏󋵍X�V
void keyboard_Update(){
	char tmpkey[256];//���݂̃L�[���͏󋵂��i�[����
	GetHitKeyStateAll(tmpkey);//���ׂẴL�[�̓��͏󋵂𓾂�
	for (int i = 0; i < 256; i++){
		if (tmpkey[i] != 0) {//i�Ԗڂ̃L�[��������Ă���Ƃ�
			key[i]++;//���Z
		}
		else//�L�[��������ĂȂ���
		{
			key[i] = 0;//0�ɂ���
		}
	}
}

//KeyBoard�̃L�[�̓��͏󋵂��K������
int keyboard_Get(int keyCode){
	return key[keyCode];//KeyCode�̓��͏�Ԃ�Ԃ�
}