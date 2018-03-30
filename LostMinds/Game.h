#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class ColliderComponent;

using namespace std;


class Game {
public:
	Game();
	~Game();
	void init(const string &title, int width, int height);
	void pollEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static void AddTile(int srcX, int srcY, int x, int y);
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static vector<ColliderComponent*> colliders;
	static bool isRunning;

private:
	string _title;
	int _width = 1280, _height = 768;
	int tickCount = 0;

	SDL_Window *window = nullptr;
};