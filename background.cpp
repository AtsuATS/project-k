#include "Dxlib.h"

int GHandle;
int bgm;
//�X�N���[����y���W
static int bgmove_y;

//�w�i������
void background_Initialize(void) {
	int bgmove_y = 0;
	GHandle = LoadGraph("GF\\back_ground.png");
	bgm = LoadSoundMem("BGM\\testBGM.wav");
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);


}

//�w�i�X�V
void background_Update(void) {
	//�w�i�̑���
	bgmove_y += 3;
	if (bgmove_y == 600)  bgmove_y = 0;
}

//�w�i�`��
void background_Draw(void) {
	DrawGraph(0, bgmove_y, GHandle, TRUE);
	DrawGraph(0, bgmove_y-600, GHandle, TRUE);

}

//�������I������
void background_Finalize(void) {
	DeleteGraph(GHandle);
	DeleteSoundMem(bgm);

}