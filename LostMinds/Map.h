#pragma once
#include <string>

class Map {
public:
	Map(std::string tID, int _mapScale, int _tileSize);
	~Map();

	void loadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int x, int y);

private:
	std::string textureID;
	int mapScale;
	int tileSize;
	int scaledSize;
};