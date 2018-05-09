#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include <sstream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,3840,2304};

ResourceManager* Game::resources = new ResourceManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& clock(manager.addEntity());
auto& label(manager.addEntity());

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

	if (TTF_Init() == -1) {
		std::cerr << "Failed to initialize TrueTypeFont!" << std::endl;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cerr << "Failed to create mixer!" << std::endl;
	}

	resources->AddTexture("terrain", "res/tiles.png");
	resources->AddTexture("player", "res/player.png");
	resources->AddTexture("projectile1", "res/projectile1.png");
	resources->AddFont("censcbk", "res/censcbk.ttf", 16);
	resources->addMusic("theme", "res/MusicBox.mp3");
	resources->addEffect("clockSound", "res/ticking_clock.wav");

	map = new Map("terrain", 4, 16);

	map->loadMap("res/map.map", 80, 48);

	player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addComponent<SoundComponent>("theme");
	player.addGroup(groupPlayers);
	SDL_Color white = { 255, 255, 255, 255 };
	label.addComponent<UILabel>(10, 10, "Test String", "censcbk", white);
	clock.addComponent<TransformComponent>(2212.0, 1024.0);
	clock.addComponent<SoundComponent>("clockSound", player);

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

	std::stringstream ss;
	ss << "Player position: " << playerPos;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "censcbk");

	manager.refresh();
	manager.update();

	for (auto& collider : colliders) {
		SDL_Rect col = collider->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(col, playerCol)) {
			if (collider->getComponent<ColliderComponent>().tag == "clock") {
				label.getComponent<UILabel>().SetLabelText("You have found the clock and can now read a piece of the mystery:", "censcbk");
			}
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
	
	label.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}