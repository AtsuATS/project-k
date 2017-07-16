#include "DxLib.h"
#include "key.h"
#include "stage.h"
#include "grobal.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetMainWindowText("project-k");//windows�̖��O��t����
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
	 stage_Draw();

	
	 //ScreenFlip();
	}
	//Fina
	stage_Finalize();

	DxLib_End(); // DX���C�u�����I������
	return 0;
}