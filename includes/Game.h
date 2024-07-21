#include "MainMenu.h"

class Game {

    private:
        sf::RenderWindow win;
        MainMenu *mainMenu;

    public:
        Game();
        ~Game();
        void Run();
        void Update();
        void Draw();
};
