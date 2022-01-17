#pragma once
#include <map>
#include <vector>
#include <grrlib.h>
#include "Engine.h"
typedef void(*drawCB)(int x, int y, int w, int h, uint32_t col1, uint32_t col2);
drawCB defaultCB;
enum class Tetronimos {
	STet = 1,
	ZTet = 2,
	ITet = 3,
	LTet = 4,
	JTet = 5,
	TTet = 6,
	OTet = 7
};
std::map<int, std::vector<std::vector<std::vector<bool>>>> tets = {
	{(int)Tetronimos::STet, 
	{
		{
			{0,0,1,1},
	        {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
		},
	    {
		    {0,0,1,0},
	        {0,0,1,1},
	        {0,0,0,1},
	        {0,0,0,0}
        },
	    {
			{0,0,0,0},
			{0,0,1,1},
			{0,1,1,0},
			{0,0,0,0}
		},
	    {
			{0,1,0,0},
			{0,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		}
    }
	},
	{(int)Tetronimos::ZTet,
	{
		{
			{0,1,1,0},
			{0,0,1,1},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,1},
			{0,0,1,1},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,0,1,1},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,1,1,0},
			{0,1,0,0},
			{0,0,0,0}
		}
	}
	},
	{(int)Tetronimos::ITet,
	{
		{
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		}
	}
	},
	{(int)Tetronimos::LTet,
	{
		{
			{0,0,0,1},
			{0,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,1},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,1},
			{0,1,0,0},
			{0,0,0,0}
		},
		{
			{0,1,1,0},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,0,0}
		}
	}
	},
	{(int)Tetronimos::JTet,
	{
		{
			{0,1,0,0},
			{0,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,1,1},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,1},
			{0,0,0,1},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,0,1,0},
			{0,1,1,0},
			{0,0,0,0}
		}
	}
	},
	{(int)Tetronimos::TTet,
	{
		{
			{0,0,1,0},
			{0,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,0,1,1},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,1},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		}
	}
	},
	{(int)Tetronimos::OTet,
	{
		{
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0},
			{0,0,0,0}
		}
	}
	}
};
namespace Tetronimo {
	struct BlockInf {
		bool inActive = false;
		int offsetX = 0;
		int offsetY = 0;
	};
	class Ghost {
	public:
		int x = 0;
		int y = 0;
		int w = 16;
		int h = 16;
		uint32_t col1 = RGBA(255, 0, 0, 128);
		uint32_t col2 = RGBA(255, 255, 255, 255);
		drawCB drw; // default
		Ghost(BlockInf* bl, uint32_t col, drawCB dr) {
			for (int i = 0; i < 4; i++) {
				blocks[i] = bl[i];
			}
			unsigned char* arr = (unsigned char*)&col;
			col1 = RGBA(arr[0], arr[1], arr[2], 128);
			drw = dr;
		}
		void draw() {
			for (int i = 0; i < 4; i++) {
				drw(blocks[i].offsetX + x, blocks[i].offsetY + y, w, h, col1, col2);
			}
		}
		BlockInf blocks[4];
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
				if (!(blocks[i].inActive)) {
					drw(blocks[i].offsetX + x, blocks[i].offsetY + y, w, h, col1, col2);
				}
			}
		}
		void refresh() {
			int i = 0;
			switch (type) {
			case Tetronimos::STet:
				col1 = RGBA(0, 255, 0, 255);
				break;
			case Tetronimos::ZTet:
				col1 = RGBA(255, 0, 0, 255);
				break;
			case Tetronimos::ITet:
				col1 = RGBA(0, 255, 255, 255);
				break;
			case Tetronimos::JTet:
				col1 = RGBA(0, 0, 255, 255);
				break;
			case Tetronimos::LTet:
				col1 = RGBA(255, 215, 0, 255);
				break;
			case Tetronimos::TTet:
				col1 = RGBA(238, 130, 238, 255);
				break;
			case Tetronimos::OTet:
				col1 = RGBA(255, 255, 0, 255);
				break;
			}
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