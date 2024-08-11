#include "MenuOption.h"

void MenuOption::SetActive(bool active) {
    isActive = active;
}

bool MenuOption::GetActive() const {
    return isActive;
}

void MenuOption::SetEnabled(bool enabled) {
    isEnabled = enabled;
}

bool MenuOption::GetEnabled() const {
    return isEnabled;
}
