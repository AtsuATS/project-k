#include "DxLib.h"
#include "key.h"
#include "stage.h"
#include "grobal.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetMainWindowText("Death Stalker");//windowsの名前を付ける
	SetGraphMode(800, 600, 16);//windowsのサイズを決める
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	//Init
	stage_Initialize();

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	//ここからゲームのループ
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

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}