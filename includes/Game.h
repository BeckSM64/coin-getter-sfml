#include "MainMenu.h"
#include "MainGameScreen.h"

class Game {

    private:
        sf::RenderWindow win;
        MainMenu *mainMenu;
        MainGameScreen *mainGameScreen;


    public:
        Game();
        ~Game();
        void Run();
        void Update();
        void Draw();
};
