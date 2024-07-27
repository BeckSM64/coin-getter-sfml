#include "ResourceManager.h"
#include <iostream>

bool ResourceManager::LoadTexture(const std::string& name, const std::string& filename) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename)) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return false;
    }
    textures[name] = std::move(texture);
    return true;
}

sf::Texture& ResourceManager::GetTexture(const std::string& name) {
    return *textures.at(name);
}

bool ResourceManager::LoadFont(const std::string& name, const std::string& filename) {
    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(filename)) {
        std::cerr << "Failed to load font: " << filename << std::endl;
        return false;
    }
    fonts[name] = std::move(font);
    return true;
}

sf::Font& ResourceManager::GetFont(const std::string& name) {
    return *fonts.at(name);
}

// bool ResourceManager::LoadSoundBuffer(const std::string& name, const std::string& filename) {
//     auto soundBuffer = std::make_unique<sf::SoundBuffer>();
//     if (!soundBuffer->loadFromFile(filename)) {
//         std::cerr << "Failed to load sound buffer: " << filename << std::endl;
//         return false;
//     }
//     soundBuffers[name] = std::move(soundBuffer);
//     return true;
// }

// sf::SoundBuffer& ResourceManager::GetSoundBuffer(const std::string& name) {
//     return *soundBuffers.at(name);
// }

void ResourceManager::InitializeResources() {
    LoadTexture("player", "sprites/player.png");
    LoadTexture("enemy", "sprites/enemy.png");
    LoadTexture("coin", "sprites/coin.png");
    LoadFont("retroFont", "fonts/RetroComputer.ttf");
    // LoadSoundBuffer("explosion", "sounds/explosion.wav");
}
