#include <iostream>
#include <conio.h>
#include <Windows.h>

class Point {
public:
	int x;
	int y;
	Point(int x = NULL, int y = NULL) : x(x), y(y){}
};

void fillMap(char gameMap[][120]);
void printMap(char gameMap[][120]);

int main() {

	Point coordinate[3600];
	char gameMap[30][120];
	fillMap(gameMap);
	int snakeSize = 10;
	char partOfSnake = 'o';

	int nextXpos = 10;
	int nextYpos = 10;
	int tmpPosX = nextXpos;
	int tmpPosY = nextYpos;

	coordinate[0].x = nextXpos;
	coordinate[0].y = nextYpos;

	char direction = 'd';
	bool error = false;

	int XposBeforeLoop;
	int YposBeforeLoop;
	int tmpX;
	int tmpY;
	
	while (!error) {
		if (_kbhit()) {
			direction = _getch();
		}
		switch (direction) {
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
			error = true;
		}
		XposBeforeLoop = nextXpos;
		YposBeforeLoop = nextYpos;
		
		for (int i = 0; i < snakeSize; i++) {
			tmpX = coordinate[i].x;
			tmpY = coordinate[i].y;
			gameMap[coordinate[i].y][coordinate[i].x] = ' ';
			coordinate[i].x = nextXpos;
			coordinate[i].y = nextYpos;
			gameMap[coordinate[i].y][coordinate[i].x] = 'o';
			nextXpos = tmpX;
			nextYpos = tmpY;
		}
		nextXpos = XposBeforeLoop;
		nextYpos = YposBeforeLoop;

		

		//for (int i = 0; i < snakeSize; i++) {
		//	tmpPosX = coordinate[i].x;
		//	tmpPosY = coordinate[i].y;
		//	gameMap[coordinate[i].y][coordinate[i].x] = ' ';
		//	coordinate[i].x = nextXpos;
		//	coordinate[i].y = nextYpos;
		//	gameMap[coordinate[i].y][coordinate[i].x] = partOfSnake;
		//}
		printMap(gameMap);
		Sleep(50);
		system("cls");
	}

	//printMap(gameMap);
}
void fillMap(char gameMap[][120]) {
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
void printMap(char gameMap[][120]) {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 120; j++) {
			std::cout << gameMap[i][j];
		}
		std::cout << '\n';
	}
}