#include "DxLib.h"
#include "key.h"
#include "stage.h"
#include "grobal.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetMainWindowText("Death Stalker");//windows�̖��O��t����
	SetGraphMode(800, 600, 16);//windows�̃T�C�Y�����߂�
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	//Init
	stage_Initialize();

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	//��������Q�[���̃��[�v
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		keyboard_Update();

		//Update
		stage_Update();

		
		//Draw
		if (status == 0)DrawFormatString(350, 300, GetColor(255, 255, 255), "PUSH S");
		if (keyboard_Get(KEY_INPUT_S)> 0) {
			status++;
		}
		if (status >= 1) {
			stage_Draw();
			if (keyboard_Get(KEY_INPUT_X) > 0 && finish_t >= 500) break;
			if (keyboard_Get(KEY_INPUT_Z) > 0 && finish_t >= 500) {
				stage_Finalize();
				stage_Initialize();
				finish_t = 0;
				t = 0;
				score = 0;
			}
		}
		//ScreenFlip();
	}
	//Fina
	stage_Finalize();

	DxLib_End(); // DX���C�u�����I������
	return 0;
}