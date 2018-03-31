#pragma once

#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component {
public:

	SDL_Texture * texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;
	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int x, int y, const char* path) {
		texture = TextureManager::loadTexture(path);

		position.x = (float)x;
		position.y = (float)y;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 16;

		destRect.x = x;
		destRect.y = y;
		destRect.w = destRect.h = 64;
	}

	void update() override {
		destRect.x = (int)position.x - Game::camera.x;
		destRect.y = (int)position.y - Game::camera.y;
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};