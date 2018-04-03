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

	TileComponent(int srcX, int srcY, int x, int y, int tileSize, int tileScale, std::string id) {
		texture = Game::resources->GetTexture(id);

		position.x = (float)x;
		position.y = (float)y;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tileSize;

		destRect.x = x;
		destRect.y = y;
		destRect.w = destRect.h = tileSize * tileScale;
	}

	void update() override {
		destRect.x = (int)position.x - Game::camera.x;
		destRect.y = (int)position.y - Game::camera.y;
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};