#ifndef MAP_H
#define MAP_H

class Map {
	char gameMap[30][120];
public:
	Map();
	void printMap()const;
	void setSignInGameMap(int posY, int posX, char sign);
	char getSignFromGameMap(int posY, int posX) { return gameMap[posY][posX]; }
};

#endif //MAP_H