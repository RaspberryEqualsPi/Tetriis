#pragma once // I AM TIRED OF TETRIS'S DUMBASS ROTATION SYSTEM, WHY DO THEY HAVE TO MAKE IT SO COMPLICATED FOR A GODDAMN GAME ABOUT DROPPING BLOCKS
#include <vector>
#include "Tetronimo.h"
std::vector<std::pair<int, int>> z2o = { {0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
std::vector<std::pair<int, int>> o2z = { {0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2} };
std::vector<std::pair<int, int>> o2t = { {0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2} };
std::vector<std::pair<int, int>> t2o = { {0, 0}, {-1,0}, {-1, -1}, {0, 2}, {-1, 2} };
std::vector<std::pair<int, int>> t23 = { {0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2} };
std::vector<std::pair<int, int>> t22 = { {0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
std::vector<std::pair<int, int>> t20 = { {0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
std::vector<std::pair<int, int>> z23 = { {0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2} };
std::vector<std::pair<int, int>> getOffsets(Tetronimos type, int from, int to) {
	if (type == Tetronimos::ITet) {
		return { {0,0} }; // temporary, don't wanna deal with the bs of making a whole entire new set of kick tables JUST FOR A SINGLE FUCKING PIECE
	}
	else {
		if (from == 0 && to == 1) {
			return z2o;
		}
		if (from == 1 && to == 0) {
			return o2z;
		}
		if (from == 1 && to == 2) {
			return o2t;
		}
		if (from == 2 && to == 1) {
			return t2o;
		}
		if (from == 2 && to == 3) {
			return t23;
		}
		if (from == 3 && to == 2) {
			return t22;
		}
		if (from == 3 && to == 0) {
			return t20;
		}
		if (from == 0 && to == 3) {
			return z23;
		}
	}
}