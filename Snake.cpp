
#include <iostream>
#include <Windows.h>
#include <conio.h>

void drawBoard(char board[][120]);
void fillBoard(char board[][120]);
void doMove(char board[][120], char snakeHead);
bool isEmptyCell(char board[][120], int row, int column);

int main() {
	char board[30][120];
	fillBoard(board);
	drawBoard(board);

	char snakeHead = 'o';
	board[10][10] = snakeHead;
	doMove(board, snakeHead);

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
void doMove(char board[][120], char snakeHead) {
	int x = 10;
	int y = 10;
	int error = 1;
	char direction = 'd';

	while (error) {
		Sleep(100);
		system("cls");

		drawBoard(board);

		if (_kbhit()) {
			direction = _getch();
		}
		switch (direction) {
		case 'd': {
			board[x][y++] = ' ';
			if (!isEmptyCell(board, x, y)) {
				error = 0;
			}
			board[x][y] = snakeHead;
		}
				break;
		case 'a': {
			board[x][y--] = ' ';
			if (!isEmptyCell(board, x, y)) {
				error = 0;
			}
			board[x][y] = snakeHead;
		}
				break;
		case 's': {
			board[x++][y] = ' ';
			if (!isEmptyCell(board, x, y)) {
				error = 0;
			}
			board[x][y] = snakeHead;
		}
				break;
		case 'w': {
			board[x--][y] = ' ';
			if (!isEmptyCell(board, x, y)) {
				error = 0;
			}
			board[x][y] = snakeHead;
		}
				break;
		default: {
			std::cout << "Smieszki heheszki :)\n";
			error = 0;
		}
		}
	}
	system("cls");
	drawBoard(board);
}
bool isEmptyCell(char board[][120], int row, int column) {
	if (board[row][column] == ' ') {
		return true;
	}
	return false;
}