// this was originally meant to be easy to port but mid-way i decided "it's easier to just make it go wii all the way"
// also, this is intended to be played with a sideways remote
/*	
	looking at this now, as of 6/18/22 (this thing was last updated in april), I realize I could have made things simpler
	by just making an array of 1's and 0's representing cells taken on the screen, and then having an array of 4 integers
	representing the positions in the array of each cell corresponding to the current tetrinimo
*/
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
	eng.w = 16;
	eng.h = 16;
	eng.start();
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
		//GRRLIB_PrintfTTF(0, 0, arcade, std::to_string(eng.statueTets.size()).c_str(), 11, RGBA(255, 255, 255, 255));
		//GRRLIB_Printf(0, 0, unispace, RGBA(255, 255, 255, 128), 1, std::to_string(eng.statueTets.size()).c_str()); // prints out the amount of tetriminos on screen
		eng.render();
		GRRLIB_Render();
	}
	GRRLIB_FreeTTF(arcade);
	GRRLIB_Exit();
	StopOgg();
	return 0;
}
