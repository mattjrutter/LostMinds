#pragma once
#include <string>
using namespace std;

class Map {
public:
	Map();
	~Map();

	static void loadMap(string path, int sizeX, int sizeY);

private:
};