#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "ResourceManager.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,3840,2304};

ResourceManager* Game::resources = new ResourceManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());

Game::Game() {}

Game::~Game() {}

void Game::init(const std::string &title, int width, int height) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "SDL_INIT_VIDEO Failed to initialize!: " << SDL_GetError() << std::endl;
	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
		std::cerr << "SDL Image Failed to initialize!: " << SDL_GetError() << std::endl;
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
		std::cerr << "Failed to Create Window!: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr) {
		std::cerr << "Failed to Create Renderer!: " << SDL_GetError() << std::endl;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	resources->AddTexture("terrain", "res/tiles.png");
	resources->AddTexture("player", "res/player.png");
	resources->AddTexture("projectile1", "res/projectile1.png");

	map = new Map("terrain", 4, 16);

	map->loadMap("res/map.map", 80, 48);

	player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	resources->CreateProjectile(Vector2D(600, 600), Vector2D(1, 0), 400, 1, "projectile1");
}

auto& mapTiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

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
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto& collider : colliders) {
		SDL_Rect col = collider->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(col, playerCol)) {
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& projectile : projectiles) {
		SDL_Rect col = projectile->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(col, playerCol)) {
			projectile->destroy();
		}
	}
	
	camera.x = (int)player.getComponent<TransformComponent>().position.x - 576;
	camera.y = (int)player.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0) 
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}

void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& mapTile : mapTiles) {
		mapTile->draw();
	}
	//for (auto& collider : colliders) { collider->draw(); }
	for (auto& player : players) {
		player->draw();
	}
	for (auto& projectile : projectiles) {
		projectile->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}