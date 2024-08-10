#include "SettingsManager.h"
#include <fstream>
#include <iostream>

void SettingsManager::InitializeSettings() {

    // Load or create settings
    std::ifstream inputFile("settings.json");
    if (inputFile.is_open()) {
        inputFile >> settings;
    } else {
        nlohmann::json resolutionSettings;
        resolutionSettings["width"] = 1920;
        resolutionSettings["height"] = 1080;
        settings["Resolution"] = resolutionSettings;
        settings["DisplayMode"] = sf::Style::Default; // 0 for borderless
        std::ofstream outputFile("settings.json");
        outputFile << settings.dump(4); // Pretty print with 4 spaces

        // sf::Style::None: 0 (No styles)
        // sf::Style::Titlebar: 1 (Binary 0001)
        // sf::Style::Resize: 2 (Binary 0010)
        // sf::Style::Close: 4 (Binary 0100)
        // sf::Style::Fullscreen: 8 (Binary 1000)
        // sf::Style::Default: 7 (Binary 0111, combination of Titlebar | Resize | Close)
    }

    // Valid resolutions map
    validResolutionsMap[0] = GetResolutionAsString(sf::Vector2f(1920, 1080));
    validResolutionsMap[1] = GetResolutionAsString(sf::Vector2f(1600, 900));
    validResolutionsMap[2] = GetResolutionAsString(sf::Vector2f(1280, 720));

    // Valid display modes map
    validDisplayModesMap[0] = GetDisplayModeAsString(sf::Style::None);
    validDisplayModesMap[1] = GetDisplayModeAsString(sf::Style::Fullscreen);
    validDisplayModesMap[2] = GetDisplayModeAsString(sf::Style::Default);
}

sf::Vector2f SettingsManager::GetResolution() const {

    sf::Vector2f resolution = sf::Vector2f();
    if (settings.contains("Resolution")) {
        resolution.x = settings["Resolution"]["width"];
        resolution.y = settings["Resolution"]["height"];
    }
    return resolution;
}

sf::Uint32 SettingsManager::GetDisplayMode() const {

    sf::Uint32 displayMode = sf::Style::Default;
    if (settings.contains("DisplayMode")) {
        displayMode = settings["DisplayMode"];
    }
    return displayMode;
}

std::string SettingsManager::GetResolutionAsString(sf::Vector2f resolution) const {

    std::string resolutionString = std::to_string(static_cast<int>(resolution.x)) + "x" + std::to_string(static_cast<int>(resolution.y));
    return resolutionString;
}

std::string SettingsManager::GetDisplayModeAsString(sf::Uint32 displayMode) const {

    std::string displayModeString = "";
    std::cout << "DISPLAY MODE: " << displayMode << std::endl;
    switch (displayMode) {
        case 0:
            displayModeString = "Borderless";
            break;
        case 7:
            displayModeString = "Windowed";
            break;
        case 8:
            displayModeString = "Fullscreen";
            break;
        default:
            displayModeString = "Windowed"; // Make windowed default for invalid options
            break;
    }

    return displayModeString;
}

std::map<int, std::string> SettingsManager::GetValidResolutionMap() const {

    return validResolutionsMap;
}

std::map<int, std::string> SettingsManager::GetValidDisplayModesMap() const {

    return validDisplayModesMap;
}

sf::Uint32 SettingsManager::GetDisplayModeFromString(std::string displayModeString) const {

    sf::Uint32 displayMode = sf::Style::Default;
    if ("Fullscreen" == displayModeString) {
        displayMode = sf::Style::Fullscreen;
    } else if ("Borderless" == displayModeString) {
        displayMode = sf::Style::None;
    } else {
        displayMode = sf::Style::Default;
    }

    return displayMode;
}

sf::Vector2f SettingsManager::GetResolutionFromString(std::string resolutionString) const {

    sf::Vector2f resolution = sf::Vector2f(1920, 1080);
    if ("1920x1080" == resolutionString) {
        resolution = sf::Vector2f(1920, 1080);
    } else if ("1600x900" == resolutionString) {
        resolution = sf::Vector2f(1600, 900);
    } else {
        resolution = sf::Vector2f(1280, 720);
    }
    
    return resolution;
}

void SettingsManager::SetResolution(sf::Vector2f resolution) {

    // Load or create settings
    std::ifstream inputFile("settings.json");
    if (inputFile.is_open()) {

        nlohmann::json resolutionSettings;
        resolutionSettings["width"] = static_cast<int>(resolution.x);
        resolutionSettings["height"] = static_cast<int>(resolution.y);
        settings["Resolution"] = resolutionSettings;
        std::ofstream outputFile("settings.json");
        outputFile << settings.dump(4); // Pretty print with 4 spaces
    }
}

void SettingsManager::SetDisplayMode(sf::Uint32 displayMode) {
    
    // Load or create settings
    std::ifstream inputFile("settings.json");
    if (inputFile.is_open()) {

        settings["DisplayMode"] = displayMode;
        std::ofstream outputFile("settings.json");
        outputFile << settings.dump(4); // Pretty print with 4 spaces
    }
}
