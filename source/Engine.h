#pragma once
#include <time.h>
#include <string>
#include "pthread.h"
#include "Tetronimo.h"
#include "arcadettf.h"
#include "tetris.h"
#define GRRLIB_CALLBACK GRRLIB_CB
float gravity = 0.01667;
float dropGrav = gravity;
int level = 1;
std::string debugval;
std::string curPrint;
GRRLIB_texImg* TetrisPNG;
GRRLIB_texImg* Orange;
GRRLIB_texImg* Red;
GRRLIB_texImg* Yellow;
GRRLIB_texImg* Green;
GRRLIB_texImg* Cyan;
GRRLIB_texImg* Blue;
GRRLIB_texImg* Purple;
GRRLIB_texImg* Gray;
GRRLIB_ttfFont* arcade;
std::vector<Tetronimos> allTets = { Tetronimos::STet, Tetronimos::JTet, Tetronimos::LTet, Tetronimos::ITet, Tetronimos::OTet, Tetronimos::ZTet, Tetronimos::TTet };
bool rgbCmp(unsigned char* rgb, unsigned char r, unsigned char g, unsigned char b) {
	return rgb[0] == r && rgb[1] == g && rgb[2] == b;
}
void GRRLIB_CB(float x, float y, float w, float h, uint32_t col1, uint32_t col2) {
	//GRRLIB_Rectangle(x * w, y * h, w, h, col1, true);
	//GRRLIB_Rectangle(x * w + ((w / 16) * 2), y * h + ((h / 16) * 2), w - ((w / 16) * 4), h - ((w / 16) * 4), col2, true);
	unsigned char rgb[3];
	unsigned char* arr = (unsigned char*)&col1;
	rgb[0] = arr[0];
	rgb[1] = arr[1];
	rgb[2] = arr[2];
	if (rgbCmp(rgb, 255, 0, 0)) {
		GRRLIB_DrawImg(x * w, y * h, Red, 0, (float)w / 32.f, (float)h / 32.f, RGBA(255, 255, 255, arr[3]));
	}else if (rgbCmp(rgb, 0, 255, 0)) {
		GRRLIB_DrawImg(x * w, y * h, Green, 0, (float)w / 32.f, (float)h / 32.f, RGBA(255,255,255, arr[3]));
	}else if (rgbCmp(rgb, 0, 255, 255)) {
		GRRLIB_DrawImg(x * w, y * h, Cyan, 0, (float)w / 32.f, (float)h / 32.f, RGBA(255, 255, 255, arr[3]));
	}else if (rgbCmp(rgb, 255, 215, 0)) {
		GRRLIB_DrawImg(x * w, y * h, Orange, 0, (float)w / 32.f, (float)h / 32.f, RGBA(255, 255, 255, arr[3]));
	}else if (rgbCmp(rgb, 0, 0, 255)) {
		GRRLIB_DrawImg(x * w, y * h, Blue, 0, (float)w / 32.f, (float)h / 32.f, RGBA(255, 255, 255, arr[3]));
	}else if (rgbCmp(rgb, 255, 255, 0)) {
		GRRLIB_DrawImg(x * w, y * h, Yellow, 0, (float)w / 32.f, (float)h / 32.f, RGBA(255, 255, 255, arr[3]));
	}else if (rgbCmp(rgb, 238, 130, 238)) {
		GRRLIB_DrawImg(x * w, y * h, Purple, 0, (float)w / 32.f, (float)h / 32.f, RGBA(255, 255, 255, arr[3]));
	}
	//GRRLIB_DrawPart(x * w, y * h, 0, 0, 1, 1, TetrisPNG, 0, w / 32, h / 32, col1);
	//GRRLIB_DrawTile(x * w, y * h, TetrisPNG, 0, w / 32, h / 32, col1, 1);
	//GRRLIB_DrawImg(x * w, y * h, TetrisPNG, 0, (float)w / 32.f, (float)h / 32.f, col1);
}
void TetEngine_Init() {
	srand(time(NULL));
	arcade = GRRLIB_LoadTTF(ArcadeTTF, ArcadeTTF_length);
	Red = GRRLIB_CreateEmptyTexture(32, 32);
	Green = GRRLIB_CreateEmptyTexture(32, 32);
	Cyan = GRRLIB_CreateEmptyTexture(32, 32);
	Blue = GRRLIB_CreateEmptyTexture(32, 32);
	Purple = GRRLIB_CreateEmptyTexture(32, 32);
	Orange = GRRLIB_CreateEmptyTexture(32, 32);
	Yellow = GRRLIB_CreateEmptyTexture(32, 32);
	TetrisPNG = GRRLIB_LoadTexture(tetris);
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 32; y++) {
			uint32_t col = GRRLIB_GetPixelFromtexImg(x, y, TetrisPNG);
			GRRLIB_SetPixelTotexImg(x, y, Red, col);
		}
	}
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 32; y++) {
			uint32_t col = GRRLIB_GetPixelFromtexImg(x + 96, y, TetrisPNG);
			GRRLIB_SetPixelTotexImg(x, y, Green, col);
		}
	}
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 32; y++) {
			uint32_t col = GRRLIB_GetPixelFromtexImg(x, y + 32, TetrisPNG);
			GRRLIB_SetPixelTotexImg(x, y, Cyan, col);
		}
	}
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 32; y++) {
			uint32_t col = GRRLIB_GetPixelFromtexImg(x + 32, y + 32, TetrisPNG);
			GRRLIB_SetPixelTotexImg(x, y, Blue, col);
		}
	}
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 32; y++) {
			uint32_t col = GRRLIB_GetPixelFromtexImg(x + 32, y, TetrisPNG);
			GRRLIB_SetPixelTotexImg(x, y, Orange, col);
		}
	}
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 32; y++) {
			uint32_t col = GRRLIB_GetPixelFromtexImg(x + 64, y, TetrisPNG);
			GRRLIB_SetPixelTotexImg(x, y, Yellow, col);
		}
	}
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 32; y++) {
			uint32_t col = GRRLIB_GetPixelFromtexImg(x + 64, y + 32, TetrisPNG);
			GRRLIB_SetPixelTotexImg(x, y, Purple, col);
		}
	}
	defaultCB = GRRLIB_CB;
}
class TetEngine {
public:
	std::vector<Tetronimo::Tetronimo> next;
	std::vector<Tetronimos> usedTets;
	std::vector<Tetronimo::Tetronimo> statueTets;
	Tetronimo::Tetronimo curTet;
	Tetronimo::Tetronimo holdTet = Tetronimo::Tetronimo(GRRLIB_CB);
	Tetronimo::Ghost ghost = Tetronimo::Ghost(curTet.blocks, curTet.col1, GRRLIB_CB);
	int curFrame = 0;
	int timerFrame = 0;
	bool timerActive = false;
	int timerResets = 0;
	bool visible = true;
	bool hardDrop = false;
	bool alreadyHeld = false;
	int w = 16;
	int h = 16;
	int x = 96;
	int y = 96;
	void newTet() {
		alreadyHeld = false;
		curTet = Tetronimo::Tetronimo(GRRLIB_CB);
		curTet.type = next[0].type;
		curTet.refresh();
		next.erase(next.begin());
		Tetronimo::Tetronimo tet(GRRLIB_CB);
		tet.type = randomize();
		tet.refresh();
		next.push_back(tet);
		curTet.x = x / w + 3;
		curTet.y = y / h;
		timerFrame = 0;
		timerActive = false;
		visible = true;
		timerResets = 0;
		hardDrop = false;
		dropGrav = gravity;
		ghost = Tetronimo::Ghost(curTet.blocks, curTet.col1, GRRLIB_CB);
		resetGhost();
	}
	void newInstance() {
		for (int i = 0; i < 5; i++) {
			Tetronimo::Tetronimo tet(GRRLIB_CB);
			tet.type = randomize();
			tet.refresh();
			next.push_back(tet);
		}
	}
	Tetronimos randomize() {
		std::vector<Tetronimos> usable = allTets;
		for (int i = 0; i < usable.size(); i++) {
			for (int z = 0; z < usedTets.size(); z++) {
				if (usedTets[z] == usable[i]) {
					usable.erase(usable.begin() + i);
				}
			}
		}
		int chosentet = rand() % usable.size();
		usedTets.push_back(usable[chosentet]);
		if (usedTets.size() == 7) {
			usedTets.clear();
		}
		return usable[chosentet];
	}
	void resetGhost() {
		ghost.x = curTet.x;
		while (!checkLowColG()) {
			ghost.y++;
		}
	}
	void downPressed() {
		dropGrav = gravity * 20.f;
	}
	void downReleased() {
		dropGrav = gravity;
	}
	void leftHeld() {
		if (!checkLeftCol())
			curTet.x--;
		resetGhost();
	}
	void hold() {
		if (!alreadyHeld) {
			if (!(holdTet.isHoldPiece)) {
				holdTet.type = curTet.type;
				newTet();
			}
			else {
				Tetronimos curType = curTet.type;
				curTet.type = holdTet.type;
				holdTet.type = curType;
				curTet.refresh();
				curTet.y = y / 16;
			}
			holdTet.refresh();
			ghost = Tetronimo::Ghost(curTet.blocks, curTet.col1, GRRLIB_CB);
			resetGhost();
			holdTet.isHoldPiece = true;
		}
		alreadyHeld = true;
	}
	void rotate() {
		int oldRot = curTet.rot;
		if (curTet.rot != 3) {
			curTet.rot++;
		}
		else {
			curTet.rot = 0;
		}
		curTet.refresh();
		if (checkLeftColR() || checkRightColR() || checkLowColR()) {
			curTet.rot = oldRot;
			curTet.refresh();
		}
		else {
			ghost = Tetronimo::Ghost(curTet.blocks, curTet.col1, GRRLIB_CB);
		}
		resetGhost();
	}
	void rightHeld() {
		if (!checkRightCol())
			curTet.x++;
		resetGhost();
	}
	void hardDropPressed() {
		hardDrop = true;
		while (!checkLowCol()) {
			curTet.y++;
		}
		timerFrame = 30; // instant lock, tho kinda hacky
	}
	bool checkLowColG() {
		bool res = false;
		for (int i = 0; i < 4; i++) {
			if (ghost.blocks[i].offsetY + ghost.y >= 19 + y / h)
				res = true;
		}
		for (int i = 0; i < statueTets.size(); i++) {
			Tetronimo::Tetronimo tet = statueTets[i];
			for (int a = 0; a < 4; a++) {
				int x1 = tet.blocks[a].offsetX + tet.x;
				int y1 = tet.blocks[a].offsetY + tet.y;
				for (int z = 0; z < 4; z++) {
					int x2 = ghost.blocks[z].offsetX + ghost.x;
					int y2 = ghost.blocks[z].offsetY + ghost.y;
					if (x2 == x1 && y2 + 1 == y1 && !(tet.blocks[a].inActive)) {
						res = true;
					}
				}
			}
		}
		return res;
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
					if (x2 == x1 && y2 + 1 == y1 && !(tet.blocks[a].inActive)) {
						res = true;
					}
				}
			}
		}
		return res;
	}
	bool checkLowColR() {
		bool res = false;
		for (int i = 0; i < 4; i++) {
			if (curTet.blocks[i].offsetY + curTet.y > 19 + y / h)
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
					if (x2 == x1 && y2 == y1 && !(tet.blocks[a].inActive)) {
						res = true;
					}
				}
			}
		}
		return res;
	}
	bool checkLeftColG1() {
		bool res = false;
		for (int i = 0; i < statueTets.size(); i++) {
			Tetronimo::Tetronimo tet = statueTets[i];
			for (int a = 0; a < 4; a++) {
				int x1 = tet.blocks[a].offsetX + tet.x;
				int y1 = tet.blocks[a].offsetY + tet.y;
				for (int z = 0; z < 4; z++) {
					int x2 = ghost.blocks[z].offsetX + ghost.x;
					int y2 = ghost.blocks[z].offsetY + ghost.y;
					if (x2 - 1 == x1 && y2 == y1 && !(tet.blocks[a].inActive)) {
						res = true;
					}
				}
			}
		}
		return res;
	}
	bool checkRightColG1() {
		bool res = false;
		for (int i = 0; i < statueTets.size(); i++) {
			Tetronimo::Tetronimo tet = statueTets[i];
			for (int a = 0; a < 4; a++) {
				int x1 = tet.blocks[a].offsetX + tet.x;
				int y1 = tet.blocks[a].offsetY + tet.y;
				for (int z = 0; z < 4; z++) {
					int x2 = ghost.blocks[z].offsetX + ghost.x;
					int y2 = ghost.blocks[z].offsetY + ghost.y;
					if (x2 + 1 == x1 && y2 == y1 && !(tet.blocks[a].inActive)) {
						res = true;
					}
				}
			}
		}
		return res;
	}
	bool checkLeftColG() {
		bool res = false;
		for (int i = 0; i < statueTets.size(); i++) {
			Tetronimo::Tetronimo tet = statueTets[i];
			for (int a = 0; a < 4; a++) {
				int x1 = tet.blocks[a].offsetX + tet.x;
				int y1 = tet.blocks[a].offsetY + tet.y;
				for (int z = 0; z < 4; z++) {
					int x2 = ghost.blocks[z].offsetX + ghost.x;
					int y2 = ghost.blocks[z].offsetY + ghost.y;
					if (x2 - 1 == x1 && y2 == y1 && !(tet.blocks[a].inActive)) {
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
	bool checkRightColG() {
		bool res = false;
		for (int i = 0; i < statueTets.size(); i++) {
			Tetronimo::Tetronimo tet = statueTets[i];
			for (int a = 0; a < 4; a++) {
				int x1 = tet.blocks[a].offsetX + tet.x;
				int y1 = tet.blocks[a].offsetY + tet.y;
				for (int z = 0; z < 4; z++) {
					int x2 = ghost.blocks[z].offsetX + ghost.x;
					int y2 = ghost.blocks[z].offsetY + ghost.y;
					if (x2 + 1 == x1 && y2 == y1 && !(tet.blocks[a].inActive)) {
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
	bool checkLeftColR() {
		bool res = false;
		for (int i = 0; i < statueTets.size(); i++) {
			Tetronimo::Tetronimo tet = statueTets[i];
			for (int a = 0; a < 4; a++) {
				int x1 = tet.blocks[a].offsetX + tet.x;
				int y1 = tet.blocks[a].offsetY + tet.y;
				for (int z = 0; z < 4; z++) {
					int x2 = curTet.blocks[z].offsetX + curTet.x;
					int y2 = curTet.blocks[z].offsetY + curTet.y;
					if (x2 == x1 && y2 == y1 && !(tet.blocks[a].inActive)) {
						res = true;
					}
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			if (curTet.blocks[i].offsetX + curTet.x < 0 + x / w)
				res = true;
		}
		return res;
	}
	bool checkRightColR() {
		bool res = false;
		for (int i = 0; i < statueTets.size(); i++) {
			Tetronimo::Tetronimo tet = statueTets[i];
			for (int a = 0; a < 4; a++) {
				int x1 = tet.blocks[a].offsetX + tet.x;
				int y1 = tet.blocks[a].offsetY + tet.y;
				for (int z = 0; z < 4; z++) {
					int x2 = curTet.blocks[z].offsetX + curTet.x;
					int y2 = curTet.blocks[z].offsetY + curTet.y;
					if (x2 == x1 && y2 == y1 && !(tet.blocks[a].inActive)) {
						res = true;
					}
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			if (curTet.blocks[i].offsetX + curTet.x > 9 + x / w)
				res = true;
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
					if (x2 - 1 == x1 && y2 == y1 && !(tet.blocks[a].inActive)) {
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
					if (x2 + 1 == x1 && y2 == y1 && !(tet.blocks[a].inActive)) {
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
	bool checkSideColG1() {
		return checkLeftColG1() || checkRightColG1();
	}
	bool checkSideColG() {
		return checkLeftColG() || checkRightColG();
	}
	bool checkSideCol() {
		return checkLeftCol() || checkRightCol();
	}
	void drawHoldFrame(float yOffset) {
		GRRLIB_Rectangle(x - (w * 3) - (w / 2), y + (yOffset * h), w * 2 + (w / 2), h * 2, RGBA(255, 255, 255, 255), false);
		holdTet.refresh();
		if (holdTet.isHoldPiece) {
			switch (holdTet.type) {
			case Tetronimos::ITet:
				holdTet.w = w / 2;
				holdTet.h = h / 2;
				holdTet.x = (float)x / ((float)w / 2.f) - 6.5;
				holdTet.y = (float)y / ((float)w / 2) + 0.5 + (yOffset * 2);
				holdTet.draw();
				break;
			case Tetronimos::OTet:
				holdTet.w = w / 2;
				holdTet.h = h / 2;
				holdTet.x = (float)x / ((float)w / 2.f) - 6.5;
				holdTet.y = y / (w / 2) + 1 + (yOffset * 2);
				holdTet.draw();
				break;
			default:
				//if (holdTet.isHoldPiece) {
				holdTet.w = w / 2;
				holdTet.h = h / 2;
				holdTet.x = (float)x / ((float)w / 2.f) - 7;
				holdTet.y = y / (w / 2) + 1 + (yOffset * 2);
				holdTet.draw();
				break;
				//}
			}
		}
	}
	void drawNextFrame(int index, float yOffset) {
		GRRLIB_Rectangle(x + w * 10 + w, y + (yOffset * h) + ((h * 3) * index), w * 2 + (w / 2), h * 2, RGBA(255, 255, 255, 255), false);
		switch (next[index].type) {
		case Tetronimos::ITet:
			next[index].w = w / 2;
			next[index].h = h / 2;
			next[index].x = (float)x / ((float)w / 2.f) + 22.5f;
			next[index].y = (float)y / ((float)w / 2) + 0.5f + yOffset * 2 + (6.f * index);
			next[index].draw();
			break;
		case Tetronimos::OTet:
			next[index].w = w / 2;
			next[index].h = h / 2;
			next[index].x = (float)x / ((float)w / 2.f) + 22.5f;
			next[index].y = (float)y / ((float)w / 2) + 1.f + yOffset * 2 + (6.f * index);
			next[index].draw();
			break;
		default:
			next[index].w = w / 2;
			next[index].h = h / 2;
			next[index].x = x / (w / 2) + 22;
			next[index].y = y / (w / 2.f) + 1.f + yOffset * 2 + (6.f * index);
			next[index].draw();
		}
	}
	void render() {
		resetGhost();
		if (timerFrame == 30) {
			curTet.isStatue = true;
			statueTets.push_back(curTet);
			newTet();
		}
		curTet.w = w;
		curTet.h = h;
		ghost.w = w;
		ghost.h = h;
		GRRLIB_PrintfTTF(x - (w * 3) - (w / 2) + ((w * 2 + (w / 2) - (w * 4)) / 2) + w, y, arcade, "Hold", h / 2, RGBA(255, 255, 255, 255));
		GRRLIB_PrintfTTF(x + w * 10 + w + ((w * 2 + (w / 2) - (w * 4)) / 2) + w, y, arcade, "Next", h / 2, RGBA(255, 255, 255, 255));
		for (int i = 0; i < 5; i++) {
			drawNextFrame(i, 1.5f);
		}
		drawHoldFrame(1.5f);
		if (checkLowCol()) {
			timerActive = true;
		}
		//while (checkSideColG1()) {
			//ghost.y--;
		//}
		for (int i = 0; i < statueTets.size(); i++) {
			for (int z = 0; z < 4; z++) {
				int x1 = statueTets[i].blocks[z].offsetX + statueTets[i].x;
				int y1 = statueTets[i].blocks[z].offsetY + statueTets[i].y;
				for (int b = 0; b < 4; b++) {
					int x2 = curTet.blocks[b].offsetX + curTet.x;
					int y2 = curTet.blocks[b].offsetY + curTet.y;
					for (int a = 0; a < 4; a++) {
						while (y1 <= ghost.blocks[a].offsetY + ghost.y && x1 == ghost.blocks[a].offsetX + ghost.x && y2 < y1 && !(statueTets[i].blocks[z].inActive)) {
							//GRRLIB_PrintfTTF(0, 0, arcade, "bruv", 11, RGBA(255, 255, 255, 255));
							ghost.y--;
						}
					}
				}
			}
		}
		std::vector<int> coords;
		for (int y1 = y / 16; y1 < y / 16 + 20; y1++) {
			int amount = 0;
			for (int i = 0; i < statueTets.size(); i++) {
				for (int z = 0; z < 4; z++) {
					if (statueTets[i].blocks[z].offsetY + statueTets[i].y == y1 && !(statueTets[i].blocks[z].inActive)) {
						amount++;
					}
				}
			}
			if (amount == 10) {
				coords.push_back(y1);
				for (int i = 0; i < statueTets.size(); i++) {
					for (int z = 0; z < 4; z++) {
						if (statueTets[i].blocks[z].offsetY + statueTets[i].y == y1){// + h / 16) {
							statueTets[i].blocks[z].inActive = true;
							//statueTets[i].blocks[z].offsetX = -1928102980218094;
						}
					}
				}
			}
		}
		for (int i = 0; i < coords.size(); i++) {
			for (int z = 0; z < statueTets.size(); z++) {
				for (int b = 0; b < 4; b++) {
					int y1 = statueTets[z].blocks[b].offsetY + statueTets[z].y;
					if (y1 <= 15) {
						debugval = std::to_string(y1) + ", " + std::to_string(coords[i]);
					}
					if (y1 < coords[i]){// + h / 16) {
						statueTets[z].blocks[b].offsetY = statueTets[z].blocks[b].offsetY + 1;
						//debugval++;
					}
				}
			}
		}
		for (int i = 0; i < statueTets.size(); i++) {
			int inactives = 0;
			for (int z = 0; z < 4; z++) {
				if (statueTets[i].blocks[z].inActive) {
					inactives++;
				}
			}
			if (inactives == 4) {
				statueTets.erase(statueTets.begin() + i);
			}
		}
		ghost.draw();
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
			if (timerFrame != 30 && !hardDrop && !checkLowCol()) {
				curTet.y++;
			}
			curFrame = 0;
		}
		GRRLIB_Rectangle(x, y, 10 * w, 20 * h, RGBA(255, 255, 255, 255), false); // decided not to waste a bunch of time making this cross platform
	}
	TetEngine(int w1, int h1) {
		//holdTet.isHoldPiece = true;
		w = w1;
		h = h1;
		newInstance();
		newTet();
	}
	TetEngine() {
		//holdTet.isHoldPiece = true;
		newInstance();
		newTet();
	}
private:
};