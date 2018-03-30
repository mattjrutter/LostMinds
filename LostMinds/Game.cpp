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

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

const char* mapTiles = "res/tiles.png";

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

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

	isRunning = true;

	if (window == nullptr) {
		cerr << "Failed to Create Window!: " << SDL_GetError() << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr) {
		cerr << "Failed to Create Renderer!: " << SDL_GetError() << endl;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	Map::loadMap("res/map.map", 80, 48);

	player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("res/player.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
}

void Game::pollEvents() {

	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	manager.refresh();
	manager.update();

	Vector2D playerVelocity = player.getComponent<TransformComponent>().velocity;
	int playerSpeed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles) {
		t->getComponent<TileComponent>().destRect.x += (int)-(playerVelocity.x * playerSpeed);
		t->getComponent<TileComponent>().destRect.y += (int)-(playerVelocity.y * playerSpeed);
	}

	for (auto col : colliders) {
		Collision::AABB(player.getComponent<ColliderComponent>(), *col);
	}
	
}

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


void Game::AddTile(int srcX, int srcY, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, x, y, mapTiles);
	tile.addGroup(groupMap);
}