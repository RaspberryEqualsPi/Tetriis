#pragma once
#include <string>
#include "pthread.h"
#include "Tetronimo.h"
#define GRRLIB_CALLBACK GRRLIB_CB
float gravity = 0.01667;
float dropGrav = gravity;
int level = 1;
std::string curPrint;
void GRRLIB_CB(int x, int y, int w, int h, uint32_t col1, uint32_t col2) {
	GRRLIB_Rectangle(x * w, y * h, w, h, col1, true);
	//GRRLIB_Rectangle(x * w + ((w / 16) * 2), y * h + ((h / 16) * 2), w - ((w / 16) * 4), h - ((w / 16) * 4), col2, true);
}
class TetEngine {
public:
	std::vector<Tetronimo::Tetronimo> statueTets;
	Tetronimo::Tetronimo curTet = Tetronimo::Tetronimo(GRRLIB_CB);
	int curFrame = 0;
	int timerFrame = 0;
	bool timerActive = false;
	int timerResets = 0;
	bool visible = true;
	bool hardDrop = false;
	int w = 16;
	int h = 16;
	int x = 96;
	int y = 96;
	void newTet() {
		curTet.x = x / w + 3;
		curTet.y = y / h;
		timerFrame = 0;
		timerActive = false;
		visible = true;
		timerResets = 0;
		hardDrop = false;
		dropGrav = gravity;
	}
	void downPressed() {
		dropGrav = gravity * 2.f;
	}
	void downReleased() {
		dropGrav = gravity;
	}
	void leftHeld() {
		if (!checkLeftCol())
			curTet.x--;
	}
	void rightHeld() {
		if (!checkRightCol())
			curTet.x++;
	}
	void hardDropPressed() {
		hardDrop = true;
		while (!checkLowCol()) {
			curTet.y++;
		}
		timerFrame = 30; // instant lock
	}
	bool checkLowCol() {
		bool res = false;
		for (int i = 0; i < 4; i++) {
			if (curTet.blocks[i].offsetY + curTet.y >= 19 + y / h)
				res = true;
		}
		for (int i = 0; i < statueTets.size(); i++) {
			Tetronimo::Tetronimo tet = statueTets[i];
			for (int a = 0; a < 4; a++) {
				int x1 = tet.blocks[a].offsetX + tet.x;
				int y1 = tet.blocks[a].offsetY + tet.y;
				for (int z = 0; z < 4; z++) {
					int x2 = curTet.blocks[z].offsetX + curTet.x;
					int y2 = curTet.blocks[z].offsetY + curTet.y;
					if (x2 == x1 && y2 + 1 == y1) {
						res = true;
					}
				}
			}
		}
		return res;
	}
	bool checkLeftCol() {
		bool res = false;
		for (int i = 0; i < statueTets.size(); i++) {
			Tetronimo::Tetronimo tet = statueTets[i];
			for (int a = 0; a < 4; a++) {
				int x1 = tet.blocks[a].offsetX + tet.x;
				int y1 = tet.blocks[a].offsetY + tet.y;
				for (int z = 0; z < 4; z++) {
					int x2 = curTet.blocks[z].offsetX + curTet.x;
					int y2 = curTet.blocks[z].offsetY + curTet.y;
					if (x2 - 1 == x1 && y2 == y1) {
						res = true;
					}
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			if (curTet.blocks[i].offsetX + curTet.x <= 0 + x / w)
				res = true;
		}
		return res;
	}
	bool checkRightCol() {
		bool res = false;
		for (int i = 0; i < statueTets.size(); i++) {
			Tetronimo::Tetronimo tet = statueTets[i];
			for (int a = 0; a < 4; a++) {
				int x1 = tet.blocks[a].offsetX + tet.x;
				int y1 = tet.blocks[a].offsetY + tet.y;
				for (int z = 0; z < 4; z++) {
					int x2 = curTet.blocks[z].offsetX + curTet.x;
					int y2 = curTet.blocks[z].offsetY + curTet.y;
					if (x2 + 1 == x1 && y2 == y1) {
						res = true;
					}
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			if (curTet.blocks[i].offsetX + curTet.x >= 9 + x / w)
				res = true;
		}
		return res;
	}
	bool checkSideCol() {
		return checkLeftCol() || checkRightCol();
	}
	void render() {
		if (checkLowCol()) {
			timerActive = true;
		}
		if (timerFrame == 30) {
			curTet.isStatue = true;
			statueTets.push_back(curTet);
			curTet = Tetronimo::Tetronimo(GRRLIB_CB);
			newTet();
		}
		if (timerActive) {
			if (checkLowCol()) {
				timerFrame++;
				if (timerResets == 15) {
					timerFrame == 30;
				}
				if (timerFrame % 5 == 0 && timerFrame % 10 != 0) {
					visible = false;
				}
				else if (timerFrame%10==0) {
					visible = true;
				}
				if (visible) {
					curTet.draw();
				}
			}
			else {
				curTet.draw();
				timerFrame = 0;
				timerResets++;
			}
		}
		else {
			curTet.draw();
		}
		curTet.w = w;
		curTet.h = h;
		switch (level) { // lmao imagine seeing this, good thing no ones reading this, or are they?
		case 1:
			gravity = 0.01667;
			break;
		case 2:
			gravity = 0.021017;
			break;
		case 3:
			gravity = 0.026977;
			break;
		case 4:
			gravity = 0.035256;
			break;
		case 5:
			gravity = 0.04693;
			break;
		case 6:
			gravity = 0.06361;
			break;
		case 7:
			gravity = 0.0879;
			break;
		case 8:
			gravity = 0.1236;
			break;
		case 9:
			gravity = 0.1775;
			break;
		case 10:
			gravity = 0.2598;
			break;
		case 11:
			gravity = 0.388;
			break;
		case 12:
			gravity = 0.59;
			break;
		case 13:
			gravity = 0.92;
			break;
		case 14:
			gravity = 1.46;
			break;
		default:
			if (level >= 15) {
				gravity = 2.36;
			}
		}
		for (int i = 0; i < statueTets.size(); i++) {
			statueTets[i].draw();
		}
		float cur = 1.f / dropGrav;
		curFrame++;
		if (curFrame >= cur) {
			if (timerFrame != 30 && !hardDrop) {
				curTet.y++;
			}
			curFrame = 0;
		}
		GRRLIB_Rectangle(x, y, 10 * w, 20 * h, RGBA(255, 255, 255, 255), false); // decided not to waste a bunch of time making this cross platform
	}
	TetEngine(int w1, int h1) {
		w = w1;
		h = h1;
		newTet();
	}
	TetEngine() {
		newTet();
	}
private:
};