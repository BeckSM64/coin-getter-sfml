#include "SettingsManager.h"
#include <fstream>

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
        settings["DisplayMode"] = sf::Style::None; // 0 for borderless
        settings["Volume"] = 50; // Half volume by default
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
    validResolutionsMap[0] = GetResolutionAsString(sf::Vector2f(640, 360));   // qHD (Low Resolution)
    validResolutionsMap[1] = GetResolutionAsString(sf::Vector2f(854, 480));   // FWVGA (Wide VGA)
    validResolutionsMap[2] = GetResolutionAsString(sf::Vector2f(1280, 720));  // HD
    validResolutionsMap[3] = GetResolutionAsString(sf::Vector2f(1366, 768));  // HD+ (Common in Laptops)
    validResolutionsMap[4] = GetResolutionAsString(sf::Vector2f(1600, 900));  // HD+
    validResolutionsMap[5] = GetResolutionAsString(sf::Vector2f(1920, 1080)); // Full HD

    // Valid display modes map
    validDisplayModesMap[0] = GetDisplayModeAsString(sf::Style::None);
    validDisplayModesMap[1] = GetDisplayModeAsString(sf::Style::Fullscreen);
    validDisplayModesMap[2] = GetDisplayModeAsString(sf::Style::Titlebar | sf::Style::Close);
}

sf::Vector2f SettingsManager::GetResolution() const {

    sf::Vector2f resolution = sf::Vector2f();
    if (settings.contains("Resolution")) {
        resolution.x = settings["Resolution"]["width"];
        resolution.y = settings["Resolution"]["height"];
    }

    resolution = ForceValidResolution(resolution);
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
    switch (displayMode) {
        case 0:
            displayModeString = "Borderless";
            break;
        case 5:
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
        displayMode = (sf::Style::Titlebar | sf::Style::Close);
    }

    return displayMode;
}

sf::Vector2f SettingsManager::GetResolutionFromString(std::string resolutionString) const {

    // Resolution to return
    sf::Vector2f resolution = sf::Vector2f(sf::VideoMode().getDesktopMode().width, sf::VideoMode().getDesktopMode().height);

    // Delimeter to check for in string
    char delimiter = 'x';

    // Find the position of the delimiter
    size_t pos = resolutionString.find(delimiter);

    // Check if the delimiter was found
    if (pos != std::string::npos) {

        // Get the resolution width and height from the string
        std::string width = resolutionString.substr(0, pos);
        std::string height = resolutionString.substr(pos + 1);

        // Try to convert substrings to ints to pass to resolution vector creation
        try {
            resolution = sf::Vector2f(std::stoi(width), std::stoi(height));
        } catch (const std::invalid_argument& e) {
            // Do nothing
        } catch (const std::out_of_range& e) {
            // Do nothing
        }

    } else {
        sf::Vector2f resolution = sf::Vector2f(sf::VideoMode().getDesktopMode().width, sf::VideoMode().getDesktopMode().height);
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

int SettingsManager::GetIndexOfResolutionMap(sf::Vector2f resolution) const {

    sf::Vector2f screenResolution = GetResolution(); // Gets the resolution from the settings file
    int index = 0; // Just return first index if it doesn't find anything idfk anymore
    int i = 0;

    // Iterate through the map
    for (const auto& pair : validResolutionsMap) {
        if (pair.second == GetResolutionAsString(screenResolution)) {
            index = i;
            break;
        }
        i++;
    }

    return index; // This function fucking sucks
}

int SettingsManager::GetIndexOfDisplayModeMap(sf::Uint32 displayMode) const {

    sf::Uint32 screenResolution = GetDisplayMode(); // Gets the display mode from the settings file
    int index = 0;
    int i = 0;

    // Iterate through the map
    for (const auto& pair : validDisplayModesMap) {
        if (pair.second == GetDisplayModeAsString(displayMode)) {
            index = i;
            break;
        }
        i++;
    }

    return index; // This function fucking sucks part 2
}

sf::Vector2f SettingsManager::ForceValidResolution(sf::Vector2f resolution) const {
    // Get the current desktop resolution
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int desktopWidth = desktopMode.width;
    unsigned int desktopHeight = desktopMode.height;

    // Aspect ratio for 16:9
    float aspectRatio = 16.0f / 9.0f;

    // Ensure the width does not exceed the monitor width
    unsigned int validWidth = static_cast<unsigned int>(std::min(resolution.x, static_cast<float>(desktopWidth)));
    unsigned int validHeight = static_cast<unsigned int>(validWidth / aspectRatio);

    // If height exceeds the monitor height, adjust accordingly
    if (validHeight > desktopHeight) {
        validHeight = desktopHeight;
        validWidth = static_cast<unsigned int>(validHeight * aspectRatio);
    }

    // Return the adjusted resolution
    return sf::Vector2f(static_cast<float>(validWidth), static_cast<float>(validHeight));
}
