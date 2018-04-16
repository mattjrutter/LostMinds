#include "SoundManager.h"

Mix_Music* SoundManager::loadMusic(const char* fileName) {
	Mix_Music *music = Mix_LoadMUS(fileName);
	if (music == NULL){
		std::cout << "Music failed to load from filename" << std::endl;
		return false;
	}
	return music;
}

Mix_Chunk* SoundManager::loadEffect(const char* fileName) {
	Mix_Chunk *effect = NULL;
	Mix_LoadWAV(fileName);
	return effect;
}

void SoundManager::playMusic(Mix_Music* music) {
	Mix_PlayMusic(music,-1);
	std::cout << "Music Playing" << std::endl;
}

void SoundManager::playEffect(Mix_Chunk* effect) {
	Mix_PlayChannel(-1, effect, 0);
}