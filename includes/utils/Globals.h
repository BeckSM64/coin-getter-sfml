#pragma once
#include <random>

const int TIME_TO_DELAY_TITLE_COLOR_CHANGE = 100;
const int TIME_TO_DELAY_MENU_NAVIGATION = 500;
const int MENU_OPTIONS_FONT_SIZE = 60;
const float DEADZONE_THRESHOLD = 10.0f;
const float PLAYER_MOVEMENT_SPEED = 100.0f;
const float ACCELERATION = 10.0f;
const float DECELERATION = 15.0f;
const int FONT_SIZE_72 = 72;
const int FONT_SIZE_128 = 128;

enum GameState {
    MAIN_MENU,
    MAIN_GAME,
    OPTIONS_MENU,
    QUIT_GAME,
    PAUSE_MENU,
    DEBUG_MENU
};
