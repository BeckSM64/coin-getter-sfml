#include "ResourceManager.h"
#include <random>
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

bool ResourceManager::LoadSoundBuffer(const std::string& name, const std::string& filename) {
    auto soundBuffer = std::make_unique<sf::SoundBuffer>();
    if (!soundBuffer->loadFromFile(filename)) {
        std::cerr << "Failed to load sound buffer: " << filename << std::endl;
        return false;
    }
    soundBuffers[name] = std::move(soundBuffer);
    return true;
}

sf::SoundBuffer& ResourceManager::GetSoundBuffer(const std::string& name) {
    return *soundBuffers.at(name);
}

bool ResourceManager::LoadIcon(const std::string &name, const std::string &filename) {
    auto icon = std::make_unique<sf::Image>();
    if (!icon->loadFromFile(filename)) {
        std::cerr << "Failed to load icon: " << filename << std::endl;
        return false;
    }
    images[name] = std::move(icon);
    return true;
}

sf::Image &ResourceManager::GetIcon(const std::string &name) {
    return *images.at(name);
}

void ResourceManager::InitializeResources() {
    baseResolution = sf::Vector2u(1920, 1080);
    LoadTexture("player", "sprites/player.png");
    LoadTexture("enemy", "sprites/enemy.png");
    LoadTexture("coin", "sprites/coin.png");
    LoadFont("retroFont", "fonts/RetroComputer.ttf");
    LoadSoundBuffer("endo", "sounds/endo.wav");
    LoadIcon("coinGetterIcon", "sprites/player.png");
}

int ResourceManager::GetRandomNumber(int lower, int upper) {
    std::uniform_int_distribution<> distr(lower, upper);
    return distr(gen);
}

float ResourceManager::GetRandomFloat(float lower, float upper) {
    std::uniform_real_distribution<> distr(lower, upper);
    return distr(gen);
}

void ResourceManager::SetScreenResolution(sf::Vector2u resolution) {
    screenResolution = resolution;
    scaleFactor = static_cast<float>(resolution.x) / baseResolution.x;
}

sf::Vector2u ResourceManager::GetScreenResolution() const {
    return screenResolution;
}

float ResourceManager::GetScaleFactor() const {
    return scaleFactor;
}

float ResourceManager::ScaleFontSize(float baseFontSize) const {
    return baseFontSize * scaleFactor;
}
