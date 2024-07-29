#pragma once
#include <random>

const int TIME_TO_DELAY_TITLE_COLOR_CHANGE = 100;
const int TIME_TO_DELAY_MENU_NAVIGATION = 500;
const int MENU_OPTIONS_FONT_SIZE = 60;
const float PLAYER_MOVEMENT_SPEED = 10.0f;

enum GameState {
    MAIN_MENU,
    MAIN_GAME,
    QUIT_GAME
};

static int getRandomNumber(int lower, int upper) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(lower, upper);
    return distr(gen);
}

static float getRandomFloat(float lower, float upper) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(lower, upper);
    return distr(gen);
}