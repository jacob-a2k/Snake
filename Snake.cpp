
#include <iostream>
#include <conio.h>
#include <Windows.h>

class Point {
	int x;
	int y;
public:
	Point(int x = NULL, int y = NULL) : x(x), y(y) {}
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int number) { this->x = number; }
	void setY(int number) { this->y = number; }
};

class Map {
	Point coordinate[3600];
	char gameMap[30][120];
public:
	void printMap()const;
	void fillMap();
	void setSignInGameMap(int posY, int posX, char sign);
	char getSignFromGameMap(int posY, int posX) { return gameMap[posY][posX]; }
	Point* getCoordinate(int number) { return &coordinate[number]; }
};
void Map::fillMap() {
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

bool isUserChooseCorrectDirection(char chosenDirection, char actualDirection);
bool isEmptyLocationForFood(Map map, int y, int x);
bool isSnakeHitTheWallOrEatHisTail(Map map, int y, int x);

int snakeSize = 1;
char actualDirection = 'd';
char chosenDirection = actualDirection;
int nextXpos = 10;
int nextYpos = 10;
int prevPosX;
int prevPosY;
char food = 'x';

int main() {
	Map map;
	map.fillMap();
	map.getCoordinate(0)->setX(nextXpos);
	map.getCoordinate(0)->setY(nextYpos);

	bool error = false;
	int XposBeforeLoop;
	int YposBeforeLoop;

	srand(time(NULL));
	int randomRow = rand() % 29 + 1;
	int randomColumn = rand() % 119 + 1;
	while (!isEmptyLocationForFood(map,randomRow,randomColumn) ){		// tutaj pracuje na spawnowaniem jedzenia w pusty miejcu mapy
		randomRow = rand() % 29 + 1;
		randomColumn = rand() % 119 + 1;
	}
	map.setSignInGameMap(randomRow, randomColumn, food);

	while (!error) {
		if (_kbhit()) {
			chosenDirection = _getch();
		}
		if (isUserChooseCorrectDirection(chosenDirection, actualDirection)) {
			switch (chosenDirection) {
			case 'd':
				nextXpos++;
				break;
			case 's':
				nextYpos++;
				break;
			case 'w':
				nextYpos--;
				break;
			case 'a':
				nextXpos--;
				break;
			default:
				std::cout << "Something goes wrong!!!" << std::endl;
				Sleep(1000);
				error = true;
			}
			actualDirection = chosenDirection;
		}
		else {
			chosenDirection = actualDirection;
		}
		XposBeforeLoop = nextXpos;
		YposBeforeLoop = nextYpos;
		if (isSnakeHitTheWallOrEatHisTail(map, nextYpos, nextXpos)) {
			error = true;
			system("cls");
			std::cout << "\n\n\n";
			std::cout << "--------GAME OVER--------";
			Sleep(4000);
			continue;
		}
		if (map.getSignFromGameMap(nextYpos, nextXpos) == food) {
			snakeSize++;
			randomRow = rand() % 29 + 1;
			randomColumn = rand() % 119 + 1;
			while (!isEmptyLocationForFood(map, randomRow, randomColumn)) {
				randomRow = rand() % 29 + 1;
				randomColumn = rand() % 119 + 1;
			}
			map.setSignInGameMap(randomRow, randomColumn, food);
		}
		for (int i = 0; i < snakeSize; i++) {
			prevPosX = map.getCoordinate(i)->getX();
			prevPosY = map.getCoordinate(i)->getY();
			map.setSignInGameMap(map.getCoordinate(i)->getY(), map.getCoordinate(i)->getX(), ' ');
			map.getCoordinate(i)->setX(nextXpos);
			map.getCoordinate(i)->setY(nextYpos);
			map.setSignInGameMap(map.getCoordinate(i)->getY(), map.getCoordinate(i)->getX(), 'o');
			nextXpos = prevPosX;
			nextYpos = prevPosY;
		}
		nextXpos = XposBeforeLoop;
		nextYpos = YposBeforeLoop;

		map.printMap();
		Sleep(100);
		system("cls");
	}
}
bool isUserChooseCorrectDirection(char chosenDirection, char actualDirection) {
	if (actualDirection == 'd' && chosenDirection == 'a' ||
		actualDirection == 'a' && chosenDirection == 'd' ||
		actualDirection == 's' && chosenDirection == 'w' ||
		actualDirection == 'w' && chosenDirection == 's') {
		return false;
	}
	return true;
}
bool isEmptyLocationForFood(Map map,int y, int x) {
	if (map.getSignFromGameMap(y, x) == ' ') {
		return true;
	}
	return false;
}
bool isSnakeHitTheWallOrEatHisTail(Map map,int y, int x) {
	if (map.getSignFromGameMap(y, x) == '|' || map.getSignFromGameMap(y,x) == '-' ||
		map.getSignFromGameMap(y, x) == 'o') {
		return true;
	}
	return false;
}
