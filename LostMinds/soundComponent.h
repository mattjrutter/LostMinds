#pragma once
#include "Components.h"
#include "TextureManager.h"
#include <SDL.h>
#include "Animation.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include <map>

class SoundComponent : public Component {
private:
	Mix_Chunk* effect;
	Mix_Music* music;
public:
	SoundComponent() = default;
	SoundComponent(std::string id) {
		setSound(id);
		std::cout << "Music ID created" << std::endl;
	}
	~SoundComponent() {}
	void setSound(std::string id) {
		music = Game::resources->getMusic(id);
	}

	void init() override{
		std::cout << "Music Initialized" << std::endl;
		SoundManager::playMusic(music);
	}
	void update() override{

	}
};