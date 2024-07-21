#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Game.h"

std::ofstream out("output.txt");

int main() {
    std::cout.rdbuf(out.rdbuf());  // Redirect std::cout to the file
    std::cout << "Hello, World!" << std::endl;
    std::cout << std::flush;
    Game game;
    game.Run();

    return 0;
}
