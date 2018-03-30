#include "Map.h"
#include "Game.h"
#include <fstream>

Map::Map(){
}

Map::~Map() {

}

void Map::loadMap(string path, int sizeX, int sizeY) {
	char c;
	fstream mapfile;
	mapfile.open(path);

	int srcX, srcY;
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapfile.get(c);
			srcY = atoi(&c) * 16;
			mapfile.get(c);
			srcX = atoi(&c) * 16;
			Game::AddTile(srcX, srcY, x * 64, y * 64);
			mapfile.ignore();
		}
	}

	mapfile.close();
}

//size of map is 24 tiles by 40 tiles