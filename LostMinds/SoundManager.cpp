#include "SoundManager.h"

Mix_Music* SoundManager::loadMusic(const char* fileName) {
	Mix_Music* music = Mix_LoadMUS(fileName);
	return music;
}

Mix_Chunk* SoundManager::loadEffect(const char* fileName) {
	Mix_Chunk* effect = NULL;
	Mix_LoadWAV(fileName);
	return effect;
}

void SoundManager::playMusic(Mix_Music * music) {
	Mix_PlayMusic(music,-1);
}

void SoundManager::playEffect(Mix_Chunk *effect) {
	Mix_PlayChannel(-1, effect, 0);
}