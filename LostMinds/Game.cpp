#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

using namespace std;


Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

Game::Game() {}

Game::~Game() {}

void Game::init(const string &title, int width, int height) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		cerr << "SDL_INIT_VIDEO Failed to initialize!: " << SDL_GetError() << endl;
	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
		cerr << "SDL Image Failed to initialize!: " << SDL_GetError() << endl;
	}

	window = SDL_CreateWindow(
		_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width, _height,
		0
	);

	if (window == nullptr) {
		cerr << "Failed to Create Window!: " << SDL_GetError() << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr) {
		cerr << "Failed to Create Renderer!: " << SDL_GetError() << endl;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	map = new Map();
	player.addComponent<TransformComponent>(.15);
	player.addComponent<SpriteComponent>("res/player.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("res/wall.png");
	wall.addComponent<ColliderComponent>("wall");
}

void Game::pollEvents() {

	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		_closed = true;
		break;
	default:
		break;
	}
}

void Game::update() {
	manager.refresh();
	manager.update();
	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		wall.getComponent<ColliderComponent>().collider))
		player.getComponent<TransformComponent>().velocity * -1;
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->drawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}