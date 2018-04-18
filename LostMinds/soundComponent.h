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
	}

	~SoundComponent() {}
	void setSound(std::string id) {
		music = Game::resources->getMusic(id);
	}

	void init() override{
		SoundManager::playMusic(music);
	}

	void update() override{

	}
};