#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"


class KeyboardController : public Component {
public:
	TransformComponent *transform;
	SpriteComponent *sprite;
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = -1; //UP
				sprite->Play("Walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1; //LEFT
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_s:
				transform->velocity.y = 1; //DOWN
				sprite->Play("Walk");
				break;
			case SDLK_d:
				transform->velocity.x = 1; //RIGHT
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = 0; //UP
				sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0; //LEFT
				sprite->Play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0; //DOWN
				sprite->Play("Idle");
				break;
			case SDLK_d:
				transform->velocity.x = 0; //RIGHT
				sprite->Play("Idle");
				break;
			}
		}
	}
};