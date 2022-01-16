#pragma once
#include <map>
#include <vector>
#include <grrlib.h>
#include "Engine.h"
typedef void(*drawCB)(int x, int y, int w, int h, uint32_t col1, uint32_t col2);
drawCB defaultCB;
enum class Tetronimos {
	STet = 1
};
std::map<int, std::vector<std::vector<std::vector<bool>>>> tets = {
	{(int)Tetronimos::STet, 
	{
		{
			{0,0,1,1},
	        {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
		}
    }
	}
};
namespace Tetronimo {
	struct BlockInf {
		int offsetX = 0;
		int offsetY = 0;
	};
	class Tetronimo {
	public:
		int x = 0;
		int y = 0;
		int w = 16;
		int h = 16;
		int rot = 0;
		bool isStatue = false;
		Tetronimos type = Tetronimos::STet;
		uint32_t col1 = RGBA(255, 0, 0, 255);
		uint32_t col2 = RGBA(255, 255, 255, 255);
		drawCB drw; // default
		void draw() {
			for (int i = 0; i < 4; i++) {
				drw(blocks[i].offsetX + x, blocks[i].offsetY + y, w, h, col1, col2);
			}
		}
		void refresh() {
			int i = 0;
			for (int x1 = 0; x1 < 4; x1++) {
				for (int y1 = 0; y1 < 4; y1++) {
					if (tets[(int)type][rot][y1][x1] == 1) {
						blocks[i].offsetX = x1;
						blocks[i].offsetY = y1;
						i++;
					}
				}
			}
		}
		Tetronimo(drawCB dcb) {
			drw = dcb;
			refresh();
		}
		Tetronimo() {
			refresh(); 
		}
		BlockInf blocks[4];
	};
}