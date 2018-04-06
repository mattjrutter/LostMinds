#pragma once
#include "Game.h"

class SoundManager {

public:
	static Mix_Music* loadMusic(const char* fileName);
	static Mix_Chunk* loadEffect(const char* fileName);
	void playMusic(Mix_Music*);
	void playEffect(Mix_Chunk*);
};