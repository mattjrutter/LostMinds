#pragma once
#include <string>
#include <SDL.h>
#include "Components.h"
#include "TextureManager.h"

class ColliderComponent : public Component {
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int x, int y, int size)
	{
		tag = t;
		collider.x = x;
		collider.y = y;
		collider.h = collider.w = size;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
			entity->addComponent<TransformComponent>();
		transform = &entity->getComponent<TransformComponent>();

		texture = TextureManager::loadTexture("res/collisionBox.png");
		srcRect = { 0, 0, 16, 16 };
		destRect = { collider.x, collider.y, collider.w, collider.h };
	}

	void update() override
	{
		if (tag != "terrain") {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		destRect.x = collider.x - Game::camera.x;
		destRect.y = collider.y - Game::camera.y;
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};