#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>


class ResourceManager;
class ColliderComponent;

class Game {
public:
	Game();
	~Game();
	void init(const std::string &title, int width, int height);
	void pollEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static ResourceManager* resources;
	enum groupLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};

private:
	std::string _title;
	int _width = 1280, _height = 768;
	int tickCount = 0;

	SDL_Window *window = nullptr;
};