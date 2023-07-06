
#include <iostream>

class Node {
	char partOfSnake;
	Node* next;
public:
	Node(char part = 'o', Node* next = nullptr) : partOfSnake(part), next(next) {}
	Node* getNext() const {
		return next;
	}
	void fillNext(Node* newNext) { this->next = newNext; }
};

class Snake {
	Node* head;
	Node* tail;
public:
	Snake(Node* head = nullptr, Node* tail = nullptr) : head(head), tail(tail) {}
	void fillhead(Node* newHead) { this->head = newHead; }
	void filltail(Node* newTail) { this->tail = newTail; }
	Node* getHead() const {
		return head;
	}
	Node* getTail() const {
		return tail;
	}
};

class Map {
	char map[30][120];
public:
	Map();
	void refillMap(char newMap[][120]);
	void printMap(char actualMap[][120]);
};
Map::Map() {
	map[0][0] = '+';
	for (int i = 1; i < 119; ++i) {
		map[0][i] = '-';
	}
	map[0][119] = '+';
	for (int j = 1; j < 29; ++j) {
		map[j][0] = '|';
		for (int i = 1; i < 119; ++i) {
			map[j][i] = ' ';
		}
		map[j][119] = '|';
	}
	map[29][0] = '+';
	for (int i = 1; i < 119; ++i) {
		map[29][i] = '-';
	}
	map[29][119] = '+';
}
void Map::refillMap(char newMap[][120]) {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 120; j++) {
			map[i][j] = newMap[i][j];
		}
	}
}
void Map::printMap(char actualMap[][120]) {
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 120; ++j) {
			std::cout << actualMap[i][j];
		}
		std::cout << '\n';
	}
}

int main() {

	Snake snake_ptr;


}