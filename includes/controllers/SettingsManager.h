#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <memory>
#include <random>
#include <json.hpp>

class SettingsManager {
public:
    static SettingsManager& GetInstance() {
        static SettingsManager instance;
        return instance;
    }

    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;
    void InitializeSettings();
    sf::Vector2f GetResolution() const;
    sf::Uint32 GetDisplayMode() const;
    std::string GetResolutionAsString(sf::Vector2f resolution) const;
    std::string GetDisplayModeAsString(sf::Uint32 displayMode) const;
    std::map<int, std::string> GetValidResolutionMap() const;
    std::map<int, std::string> GetValidDisplayModesMap() const;
    sf::Uint32 GetDisplayModeFromString(std::string displayModeString) const;
    sf::Vector2f GetResolutionFromString(std::string resolutionString) const;
    void SetResolution(sf::Vector2f resolution);
    void SetDisplayMode(sf::Uint32 displayMode);
    int GetIndexOfResolutionMap(sf::Vector2f resolution) const;
    int GetIndexOfDisplayModeMap(sf::Uint32 displayMode) const;
    void SetVolume(int volume);
    int GetVolume() const;

private:
    SettingsManager() = default;
    ~SettingsManager() = default;
    sf::Vector2f ForceValidResolution(sf::Vector2f resolution) const;
    nlohmann::json settings;
    std::map<int, std::string> validResolutionsMap;
    std::map<int, std::string> validDisplayModesMap;
};
