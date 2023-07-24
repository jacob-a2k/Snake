#include <iostream>
#include "Map.h"

Map::Map() {
	gameMap[0][0] = '+';
	for (int i = 1; i < 119; ++i) {
		gameMap[0][i] = '-';
	}
	gameMap[0][119] = '+';
	for (int j = 1; j < 29; ++j) {
		gameMap[j][0] = '|';
		for (int i = 1; i < 119; ++i) {
			gameMap[j][i] = ' ';
		}
		gameMap[j][119] = '|';
	}
	gameMap[29][0] = '+';
	for (int i = 1; i < 119; ++i) {
		gameMap[29][i] = '-';
	}
	gameMap[29][119] = '+';
}
void Map::printMap() const {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 120; j++) {
			std::cout << gameMap[i][j];
		}
		std::cout << '\n';
	}
}
void Map::setSignInGameMap(int posY, int posX, char sign) {
	gameMap[posY][posX] = sign;
}