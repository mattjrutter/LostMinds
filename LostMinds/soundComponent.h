#pragma once
#include "Components.h"
#include "TextureManager.h"
#include <SDL.h>
#include "Animation.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Components.h"
#include <cmath>
#include <map>

class SoundComponent : public Component {
private:
	Mix_Chunk* effect;
	Mix_Music* music;
	TransformComponent* transform;
	std::string id2;
	float playerX, playerY;
public:
	SoundComponent() = default;
	SoundComponent(std::string id) {
		setSound(id);
		id2 = id;
	}
	SoundComponent(std::string id, Entity& player) {
		setSound(id);
		id2 = id;
		playerX = player.getComponent<TransformComponent>().position.x;
		playerY = player.getComponent<TransformComponent>().position.y;
	}
	~SoundComponent() {}
	void setSound(std::string id) {
		if (id == "theme")
			music = Game::resources->getMusic(id);
		else
			effect = Game::resources->getEffect(id);
	}
	void init() override{
		transform = &entity->getComponent<TransformComponent>();
		playerX = transform->position.x;
		playerY = transform->position.y;
		if (id2 == "theme") {
			SoundManager::playMusic(music);
		}
		else {
			SoundManager::playEffect(effect, getAngle(), getDistance());
		}
	}
	void update() override{
		playerX = (float)Game::camera.x+576;
		playerY = (float)Game::camera.y+320;
		SoundManager::playEffect(effect, getAngle(), getDistance());
	}
	/*
	Functions to get distance and angle for sound location
	*/
	int getDistance() {
		int dist = static_cast<int>((sqrt(pow((playerX - transform->position.x), 2) + pow((playerY - transform->position.y), 2)))/2);
		if (dist > 255)
			dist = 255;
		return dist;
	}
	int getAngle() {
		static const double TWOPI = 6.2831853071795865;
		static const double RAD2DEG = 57.2957795130823209;
		double theta = atan2(transform->position.x - playerX, transform->position.y - playerY);
		if (theta < 0.0)
			theta += TWOPI;
		int angle = static_cast<int>(RAD2DEG * theta);
		if (angle == 0)
			angle = angle + 1;
		std::cout << angle << std::endl;
		return angle;
	}
};