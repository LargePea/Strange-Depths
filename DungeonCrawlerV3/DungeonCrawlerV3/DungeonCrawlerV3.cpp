#include "Screen.h"
#include "GameManager.h"
#include "GameState.h"
#include "SpriteAtlas.h"
#include <conio.h>
#include "InventoryMenu.h"

int main()
{
    Screen::Init(); //start screen
    bool gameRunning = true;

    while (gameRunning)
    {
        GameState::SetStateMask(GameStateMask::Normal); //sanity check
        Image mainMenu = Image(MAIN_MENU, 0, std::make_pair<int, int>(0, 0));
        Screen::AddImages({ &mainMenu });
        switch (static_cast<char>(_getch()))
        {
        case 'p':
        case 'P':
            Screen::RemoveImages({ &mainMenu });
            GameManager::Init();
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
