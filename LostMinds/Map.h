#pragma once
#include "Game.h"


class Map {
public:
	Map();
	~Map();

	void loadMap(int arr[24][40]);
	void drawMap();

private:
	SDL_Rect src, dest;
	SDL_Texture* floor;
	SDL_Texture* wall;

	int map[24][40];
};