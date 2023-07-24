#ifndef SNAKE_H
#define SNAKE_H

class Snake {
	int snakeSize;
	int snakeSpeed;
	Point* head;
public:
	Snake(int size = 1, int speed = 100) : snakeSize(size), snakeSpeed(speed) { head = new Point(nullptr, 10, 10); }
	Point* getHead() const { return head; }
	void setHead(Point* newHead) { head = newHead; }
	void increaseSnakeSize() { snakeSize++; }
	int getSnakeSize() const { return snakeSize; }
	void increaseSnakeSpeed() { snakeSpeed = snakeSpeed / 2; }
	int getSnakeSpeed() const { return snakeSpeed; }
};

#endif //SNAKE-h
