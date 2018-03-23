#pragma once
#include "Game.h"

class TextureManager {

public:
	static SDL_Texture* loadTexture(const char* fileName);
	static void draw(SDL_Texture* _texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};