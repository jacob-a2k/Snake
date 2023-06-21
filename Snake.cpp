#include <iostream>
#include <windows.h>
#include <conio.h>

void fillBoard(char board[][120]);
void drawBoard(char board[][120]);

int main()
{
	char array[30][120];
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 120; ++j) {
			array[i][j] = ' ';
		}
	}
	int x = 10;
	int y = 10;
	char snakeHead = 'o';
	array[x][y] = snakeHead;
	int error = 1;
	char direction = 'd';

	// try to use kbhit();
	while (error) {
		Sleep(100);
		system("cls");
		for (int i = 0; i < 30; ++i) {
			for (int j = 0; j < 120; ++j) {
				std::cout << array[i][j];
			}
			std::cout << "\n";
		}
		if (_kbhit()) {
			direction = _getch();
		}
		switch (direction) {
		case 'd': {
			array[x][y++] = ' ';
			array[x][y] = snakeHead;
		}
				break;
		case 'a': {
			array[x][y--] = ' ';
			array[x][y] = snakeHead;
		}
				break;
		case 's': {
			array[x++][y] = ' ';
			array[x][y] = snakeHead;
		}
				break;
		case 'w': {
			array[x--][y] = ' ';
			array[x][y] = snakeHead;
		}
				break;
		default: {
			std::cout << "Smieszki heheszki :)\n";
			error = 0;
		}
		}
	}

}
void fillBoard(char board[][120]) {
	board[0][0] = '+';
	for (int i = 1; i < 119; ++i) {
		board[0][i] = '-';
	}
	board[0][119] = '+';
	for (int j = 1; j < 29; ++j) {
		board[j][0] = '|';
		for (int i = 1; i < 119; ++i) {
			board[j][i] = ' ';
		}
		board[j][119] = '|';
	}
	board[29][0] = '+';
	for (int i = 1; i < 119; ++i) {
		board[29][i] = '-';
	}
	board[29][119] = '+';
}
void drawBoard(char board[][120]) {
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 120; ++j) {
			std::cout << board[i][j];
		}
		std::cout << '\n';
	}
}
void moveToNextRightCell(char board[][120], int x, int y) {
	board[x][y] = ' ';
	board[x][y + 1] = 'o';
}