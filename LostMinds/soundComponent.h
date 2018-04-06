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
	SoundComponent() = default;
	~SoundComponent() {}
public:
	void init() override{

	}
	void draw() override {

	}
	void update() override{

	}
};