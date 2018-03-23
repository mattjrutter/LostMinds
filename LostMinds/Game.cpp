#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

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

	Map::loadMap("res/level1_16x16.map", 16, 16);

	player.addComponent<TransformComponent>(2.5);
	player.addComponent<SpriteComponent>("res/player.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("res/wall.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);
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

	for (auto col : colliders) {
		Collision::AABB(player.getComponent<ColliderComponent>(), *col);
	}
	
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& tile : tiles) {
		tile->draw();
	}
	for (auto& player : players) {
		player->draw();
	}
	for (auto& enemy : enemies) {
		enemy->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}


void Game::AddTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}