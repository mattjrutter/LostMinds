#pragma once
#include "Components.h"
#include "TextureManager.h"
#include <SDL.h>
#include "Animation.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Components.h"
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
		if (id == "theme")
			music = Game::resources->getMusic(id);
		else
			effect = Game::resources->getEffect(id);
	}

	void init() override{
		SoundManager::playMusic(music);
		if (!Mix_SetPosition(MIX_CHANNEL_POST, 90, 0)) {
			printf("Mix_SetPanning: %s\n", Mix_GetError());
		}
	}

	void update() override{

	}
};