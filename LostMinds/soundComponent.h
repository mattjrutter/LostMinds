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

/*
Functions that takes 4 double values and return an angle in degrees or distance.
*/
#include <cmath>

int getDistance(double x1, double y1, double x2, double y2) {
    return static_cast<int>(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

int getAngle(double x1, double y1, double x2, double y2) {
    static const double TWOPI = 6.2831853071795865;
    static const double RAD2DEG = 57.2957795130823209;
    // if (x1 = x2 and y1 = y2) throw an error 
    double theta = atan2(x2 - x1, y1 - y2);
    if (theta < 0.0)
        theta += TWOPI;
    return ststic_cast<int>(RAD2DEG * theta);
}