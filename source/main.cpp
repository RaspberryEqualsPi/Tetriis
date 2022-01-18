// this was originally meant to be easy to port but mid-way i decided "fuck it, it's easier to just make it go wii all the way"
// also, this is intended to be played with a sideways remote
#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <asndlib.h>
#include <grrlib.h>
#include <string>
#include <fat.h>
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
	TetEngine_Init();
	TetEngine eng;
	PlayOgg(tetris_ogg, tetris_ogg_size, 0, OGG_INFINITE_TIME);
	while(1) {
		WPAD_ScanPads();
		u32 pressed = WPAD_ButtonsDown(0);
		u32 released = WPAD_ButtonsUp(0);
		u32 held = WPAD_ButtonsHeld(0);
		if (pressed & WPAD_BUTTON_HOME) break;
		if (held & WPAD_BUTTON_LEFT) {
			eng.downPressed();
		}
		if (pressed & WPAD_BUTTON_UP) {
			eng.leftHeld();
		}
		if (pressed & WPAD_BUTTON_DOWN) {
			eng.rightHeld();
		}
		if (pressed & WPAD_BUTTON_B) {
			eng.hold();
		}
		if (pressed & WPAD_BUTTON_2) {
			eng.rotate();
		}
		if (pressed & WPAD_BUTTON_1) {
			eng.rotateC();
		}
		if (pressed & WPAD_BUTTON_RIGHT) {
			eng.hardDropPressed();
		}
		if (released & WPAD_BUTTON_LEFT) {
			eng.downReleased();
		}
		if (held & WPAD_BUTTON_UP) {
			lHeldFrame++;
			if (lHeldFrame == 10) {
				eng.leftHeld();
				lHeldFrame = 0;
			}
		}
		else {
			lHeldFrame = 0;
		}
		if (held & WPAD_BUTTON_DOWN) {
			rHeldFrame++;
			if (rHeldFrame == 10) {
				eng.rightHeld();
				rHeldFrame = 0;
			}
		}
		else {
			rHeldFrame = 0;
		}
		GRRLIB_PrintfTTF(0, 0, arcade, debugval.c_str(), 11, RGBA(255, 255, 255, 255));
		eng.render();
		GRRLIB_Render();
	}
	GRRLIB_FreeTTF(arcade);
	GRRLIB_Exit();
	StopOgg();
	return 0;
}
