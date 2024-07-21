#include <random>

const int TIME_TO_DELAY_TITLE_COLOR_CHANGE = 100;
const int MENU_OPTIONS_FONT_SIZE = 60;

int getRandomNumber(int lower, int upper) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(lower, upper);
    return distr(gen);
}
