#include "Screen.h"
#include "GameManager.h"
#include "GameState.h"
#include <conio.h>

int main()
{
    Screen::Init(); //start screen
    bool gameRunning = true;
    GameState::SetStateMask(GameStateMask::Normal); //sanity check

    while (gameRunning)
    {
        Image mainMenu = Image("Sprites\\MainMenu.txt", 0, std::make_pair<int, int>(0, 0));
        Screen::AddImages({ &mainMenu });
        switch (static_cast<char>(_getch()))
        {
        case 'p':
        case 'P':
            Screen::RemoveImages({ &mainMenu });
            GameManager::Init();
            std::cin.get(); //wait for player to enter input before loading main menu again
            break;
        case 'q':
        case 'Q':
            gameRunning = false;
            break;
        default:
            break;
        }
    }
}
