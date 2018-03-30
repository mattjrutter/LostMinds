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
				transform->velocity.y = transform->speed * (float)-1.0; //UP
				break;
			case SDLK_a:
				transform->velocity.x = transform->speed * (float)-1.0; //LEFT
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_s:
				transform->velocity.y = (float)transform->speed; //DOWN
				break;
			case SDLK_d:
				transform->velocity.x = (float)transform->speed; //RIGHT
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = 0; //UP
				break;
			case SDLK_a:
				transform->velocity.x = 0; //LEFT
				break;
			case SDLK_s:
				transform->velocity.y = 0; //DOWN
				break;
			case SDLK_d:
				transform->velocity.x = 0; //RIGHT
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			}
		}

		if (transform->velocity.x != 0 || transform->velocity.y != 0) {
			sprite->Play("Walk");
		}
		else {
			sprite->Play("Idle");
		}

	}
};