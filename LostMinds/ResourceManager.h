#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS.h"
#include "SDL_ttf.h"

class ResourceManager {
public:
	ResourceManager(Manager* man);
	~ResourceManager();

	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	void addMusic(std::string, const char* path);

	Mix_Music *getMusic(std::string);

	void addEffect(std::string, const char* path);

	Mix_Chunk *getEffect(std::string);

	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, Mix_Chunk*> effects;
	std::map<std::string, Mix_Music*> musics;
};