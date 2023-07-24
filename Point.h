#ifndef POINT_H
#define POINT_H

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
	Point operator=(const Point* newPoint) {
		return Point(this->next = newPoint->next, this->y = newPoint->y, this->x = newPoint->x);
	}
	Point* getNext() const { return next; }
	void setNext(Point* nextPoint) { next = nextPoint; }
};

#endif // POINT_H
