#include "GameObject.h"
#include "TextureManager.h"


GameObject::GameObject(const char* textureSheet, int x, int y) {
	objTexture = TextureManager::loadTexture(textureSheet);

	xpos = x;
	ypos = y;

}

void GameObject::update() {
	xpos++;
	ypos++;

	srcRect.h = 420;
	srcRect.w = 320;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.h = 80;
	destRect.w = 64;
	destRect.x = xpos;
	destRect.y = ypos;

}

void GameObject::render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}