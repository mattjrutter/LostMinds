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
	int playerX, playerY;
public:
	SoundComponent() = default;
	SoundComponent(std::string id) {
		setSound(id);
		id2 = id;
		playerX = transform->position.x;
		playerY = transform->position.y;
	}
	SoundComponent(std::string id, int pX, int pY) {
		setSound(id);
		id2 = id;
		playerX = pX;
		playerY = pY;
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
		if (!Mix_SetPosition(MIX_CHANNEL_POST, getAngle(), getDistance())) {
			printf("Mix_SetPanning: %s\n", Mix_GetError());
		}
		if (id2 == "theme") {
			SoundManager::playMusic(music);
		}
		else {
			//Mix_SetPosition(2, getAngle(), getDistance());
			SoundManager::playEffect(effect, getAngle(), getDistance());
		}
	}
	void update() override{

	}
	
	void setX(int x) {
		playerX=x;
	}

	void setY(int y) {
		playerY=y;
	}
	/*
	Functions to get distance and angle for sound location
	*/
	int getDistance() {
		int dist = static_cast<int>(sqrt(pow((playerX - transform->position.x), 2) + pow((playerY - transform->position.y), 2)));
		std::cout << playerX << " " << playerY << std::endl;
		std::cout << dist << std::endl;
		return dist;
	}

	int getAngle() {
		static const double TWOPI = 6.2831853071795865;
		static const double RAD2DEG = 57.2957795130823209;
		// if (x1 = x2 and y1 = y2) throw an error
		double theta = atan2(transform->position.x - playerX, playerY - transform->position.y);
		if (theta < 0.0)
			theta += TWOPI;
		std::cout << static_cast<int>(RAD2DEG * theta) << std::endl;
		return static_cast<int>(RAD2DEG * theta);
	}
};