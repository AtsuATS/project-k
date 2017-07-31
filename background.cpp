#include "Dxlib.h"

int GHandle;
int bgm;
//ƒXƒNƒ[ƒ‹‚ÌyÀ•W
static int bgmove_y;

//”wŒi‰Šú‰»
void background_Initialize(void) {
	int bgmove_y = 0;
	GHandle = LoadGraph("GF\\back_ground.png");
	bgm = LoadSoundMem("BGM\\testBGM.wav");
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);


}

//”wŒiXV
void background_Update(void) {
	//”wŒi‚Ì‘¬‚³
	bgmove_y += 3;
	if (bgmove_y == 600)  bgmove_y = 0;
}

//”wŒi•`Ê
void background_Draw(void) {
	DrawGraph(0, bgmove_y, GHandle, TRUE);
	DrawGraph(0, bgmove_y-600, GHandle, TRUE);

}

//ˆ—‚ğI—¹‚·‚é
void background_Finalize(void) {
	DeleteGraph(GHandle);
	DeleteSoundMem(bgm);

}