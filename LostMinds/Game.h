#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;


class Game {
public:
	Game();
	~Game();
	void init(const string &title, int width, int height);
	void pollEvents();
	void update();
	inline bool isClosed() const { return _closed; }
	void render();
	void clean();

	static SDL_Renderer *renderer;
	static SDL_Event event;

private:
	string _title;
	int _width = 1280, _height = 768;
	bool _closed = false;
	int tickCount = 0;

	SDL_Window *window = nullptr;
};