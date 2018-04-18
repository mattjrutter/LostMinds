#include "ResourceManager.h"
#include "Components.h"

ResourceManager::ResourceManager(Manager* man) : manager(man) {}

ResourceManager::~ResourceManager() {}

void ResourceManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id){
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 16, 16, 1);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}

void ResourceManager::AddTexture(std::string id, const char* path) {
	textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture* ResourceManager::GetTexture(std::string id){
	return textures[id];
}

void ResourceManager::AddFont(std::string id, std::string path, int fontSize){
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}


TTF_Font* ResourceManager::GetFont(std::string id){
	return fonts[id];
}

void ResourceManager::addMusic(std::string id, const char* path) {
	musics.emplace(id, SoundManager::loadMusic(path));
}

Mix_Music* ResourceManager::getMusic(std::string id) {
	return musics[id];
}

void ResourceManager::addEffect(std::string id, const char* path) {
	effects.emplace(id, SoundManager::loadEffect(path));
}

Mix_Chunk* ResourceManager::getEffect(std::string id) {
	return effects[id];
}