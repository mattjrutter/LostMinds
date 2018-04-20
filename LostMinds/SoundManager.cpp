#include "SoundManager.h"

Mix_Music* SoundManager::loadMusic(const char* fileName) {
	Mix_Music *music = Mix_LoadMUS(fileName);
	if (music == NULL){
		std::cerr << "Music failed to load from filename" << std::endl;
		return false;
	}
	return music;
}

Mix_Chunk* SoundManager::loadEffect(const char* fileName) {
	Mix_Chunk *effect = NULL;
	Mix_LoadWAV(fileName);
	if (effect == NULL) {
		std::cerr << "Effect failed to load from filename" << std::endl;
		return false;
	}
	return effect;
}

void SoundManager::playMusic(Mix_Music* music) {
	if (Mix_PlayMusic(music, -1) == -1) {
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
	}
}

void SoundManager::playEffect(Mix_Chunk* effect) {
	Mix_PlayChannel(-1, effect, 0);
}