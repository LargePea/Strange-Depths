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
        Screen::PrintMainMenu();
        switch (static_cast<char>(_getch()))
        {
        case 'p':
        case 'P':
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
