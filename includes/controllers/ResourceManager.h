#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <memory>
#include <random>

class ResourceManager {
public:
    static ResourceManager& GetInstance() {
        static ResourceManager instance;
        return instance;
    }

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    bool LoadTexture(const std::string& name, const std::string& filename);
    sf::Texture& GetTexture(const std::string& name);

    bool LoadFont(const std::string& name, const std::string& filename);
    sf::Font& GetFont(const std::string& name);

    bool LoadSoundBuffer(const std::string& name, const std::string& filename);
    sf::SoundBuffer& GetSoundBuffer(const std::string& name);

    void InitializeResources();

    int GetRandomNumber(int lower, int upper);

    float GetRandomFloat(float lower, float upper);

    // Optionally: Unload resources to manage memory
    // void UnloadTexture(const std::string& name);
    // void UnloadFont(const std::string& name);
    // void UnloadSoundBuffer(const std::string& name);

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers;

    std::random_device rd;
    std::mt19937 gen;
};
