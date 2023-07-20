#include <iostream>
#include <conio.h>
#include <Windows.h>

class Point {
	int y;
	int x;
	Point* next;
public:
	Point(Point* next = nullptr, int y = NULL, int x = NULL) : next(next), y(y), x(x) {}
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int number) { this->x = number; }
	void setY(int number) { this->y = number; }
	Point operator=(const Point* newPoint);
	Point* getNext() const { return next; }
	void setNext(Point* nextPoint) { next = nextPoint; }
};
Point Point::operator=(const Point* newPoint) {
	return Point(this->next = newPoint->next,this->y = newPoint->y, this->x = newPoint->x);
}

class Snake {
	Point* head;
	Point* tail;
public:
	Snake() {
		head = new Point(nullptr,10,10);
		tail = head;
	}
	Point* getHead() const { return head; }
	void setHead(Point* newHead) { head = newHead; }
	void setTail(Point* newTail) { tail = newTail; }
};

class Map {
	char gameMap[30][120];
public:
	Map();
	void printMap()const;
	void setSignInGameMap(int posY, int posX, char sign);
	char getSignFromGameMap(int posY, int posX) { return gameMap[posY][posX]; }
};
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

bool isUserChooseCorrectDirection(char chosenDirection, char actualDirection);
bool isEmptyLocationForFood(Map map, int y, int x);
bool isUserChoseCorectSign(char dir);
bool isSnakeHitTheWallOrEatHisTail(Map map, int y, int x);

char actualDirection = 'd';
char chosenDirection = actualDirection;
int nextXpos = 10;
int nextYpos = 10;
int prevPosX;
int prevPosY;
char food = 'x';

int main() {

	Snake snake;
	Map map;
	std::cout << snake.getHead()->getX() << std::endl;
	std::cout << snake.getHead()->getY() << std::endl;

	bool error = false;
	int XposBeforeLoop;
	int YposBeforeLoop;

	srand(time(NULL));
	int randomRow = rand() % 29 + 1;
	int randomColumn = rand() % 119 + 1;
	while (!isEmptyLocationForFood(map, randomRow, randomColumn)) {
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
			continue;
		}
		XposBeforeLoop = nextXpos;
		YposBeforeLoop = nextYpos;
		if (isSnakeHitTheWallOrEatHisTail(map, nextYpos, nextXpos)) {
			error = true;
			map.printMap();
			std::cout << "\n\n\n";
			std::cout << "--------GAME OVER--------";
			Sleep(4000);
			continue;
		}
		if (map.getSignFromGameMap(nextYpos, nextXpos) == food) {		// tu jest problem
			Point* newPartOfSnake = new Point;
			newPartOfSnake->setY(nextYpos);
			newPartOfSnake->setX(nextXpos);
			newPartOfSnake->setNext(snake.getHead());
			Point* current = newPartOfSnake;
			Point* penultimate = nullptr;
			while (current->getNext() != nullptr) {
				penultimate = current->getNext();
				current = current->getNext();
			}
			snake.setTail(penultimate);
			snake.setHead(newPartOfSnake);
			delete current;

			randomRow = rand() % 29 + 1;
			randomColumn = rand() % 119 + 1;
			while (!isEmptyLocationForFood(map, randomRow, randomColumn)) {
				randomRow = rand() % 29 + 1;
				randomColumn = rand() % 119 + 1;
			}
			map.setSignInGameMap(randomRow, randomColumn, food);
		}
		Point* current = snake.getHead();
		while(current != nullptr) {
			prevPosX = current->getX();
			prevPosY = current->getY();
			map.setSignInGameMap(current->getY(), current->getX(), ' ');
			current->setX(nextXpos);
			current->setY(nextYpos);
			map.setSignInGameMap(current->getY(), current->getX(), 'o');
			nextXpos = prevPosX;
			nextYpos = prevPosY;
			current = current->getNext();
		}
		delete current;
		nextXpos = XposBeforeLoop;
		nextYpos = YposBeforeLoop;

		map.printMap();
		Sleep(100);
		system("cls");
	}
}
bool isUserChooseCorrectDirection(char chosenDirection, char actualDirection) {
	if (isUserChoseCorectSign(chosenDirection)) {
		if (actualDirection == 'd' && chosenDirection == 'a' ||
			actualDirection == 'a' && chosenDirection == 'd' ||
			actualDirection == 's' && chosenDirection == 'w' ||
			actualDirection == 'w' && chosenDirection == 's') {
			return false;
		}
		return true;
	}
	return false;
}
bool isEmptyLocationForFood(Map map, int y, int x) {
	if (map.getSignFromGameMap(y, x) == ' ') {
		return true;
	}
	return false;
}
bool isSnakeHitTheWallOrEatHisTail(Map map, int y, int x) {
	if (map.getSignFromGameMap(y, x) == '|' || map.getSignFromGameMap(y, x) == '-' ||
		map.getSignFromGameMap(y, x) == 'o') {
		return true;
	}
	return false;
}
bool isUserChoseCorectSign(char dir) {
	if (dir == 'a' || dir == 's' || dir == 'd' || dir == 'w') {
		return true;
	}
	return false;
}