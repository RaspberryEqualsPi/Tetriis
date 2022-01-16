/****************************************************************************
 * OGG Playback example
 * Tantric 2009
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <asndlib.h>
#include <grrlib.h>
#include <string>
#include <fat.h>
#include "arcadettf.h"
#include "oggplayer.h"
#include "tetris_ogg.h"
#include "Engine.h"
int lHeldFrame = 0;
int rHeldFrame = 0;
int main(int argc, char **argv) {
	GRRLIB_Init();
	ASND_Init();
	WPAD_Init();
	fatInitDefault();
	//LWP_MutexInit(&engmut, false);
	GRRLIB_ttfFont* arcade = GRRLIB_LoadTTF(ArcadeTTF, ArcadeTTF_length);
	defaultCB = GRRLIB_CB;
	TetEngine eng;
	PlayOgg(tetris_ogg, tetris_ogg_size, 0, OGG_INFINITE_TIME);
	while(1) {
		WPAD_ScanPads();
		u32 pressed = WPAD_ButtonsDown(0);
		u32 released = WPAD_ButtonsUp(0);
		u32 held = WPAD_ButtonsHeld(0);
		if (pressed & WPAD_BUTTON_HOME) break;
		if (pressed & WPAD_BUTTON_DOWN) {
			eng.downPressed();
		}
		if (pressed & WPAD_BUTTON_LEFT) {
			eng.leftHeld();
		}
		if (pressed & WPAD_BUTTON_RIGHT) {
			eng.rightHeld();
		}
		if (pressed & WPAD_BUTTON_1) {
			eng.hardDropPressed();
		}
		if (released & WPAD_BUTTON_DOWN) {
			eng.downReleased();
		}
		if (held & WPAD_BUTTON_LEFT) {
			lHeldFrame++;
			if (lHeldFrame == 10) {
				eng.leftHeld();
				lHeldFrame = 0;
			}
		}
		else {
			lHeldFrame = 0;
		}
		if (held & WPAD_BUTTON_RIGHT) {
			rHeldFrame++;
			if (rHeldFrame == 10) {
				eng.rightHeld();
				rHeldFrame = 0;
			}
		}
		else {
			rHeldFrame = 0;
		}
		GRRLIB_PrintfTTF(0, 0, arcade, std::to_string(gravity).c_str(), 11, RGBA(255, 255, 255, 255));
		eng.render();
		GRRLIB_Render();
	}
	GRRLIB_FreeTTF(arcade);
	GRRLIB_Exit();
	StopOgg();
	return 0;
}
