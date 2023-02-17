#include "Screen.h"
#include "Image.h"
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <array>
#include <string>
#include "GameManager.h"
#include "GameState.h"
#include <conio.h>

int main()
{
    COORD outbuff;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND window = GetConsoleWindow();
    CONSOLE_SCREEN_BUFFER_INFO info;
    SMALL_RECT windowSize = { 0, 0, 115, 50 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    if (GetConsoleScreenBufferInfo(hConsole, &info)) {
        outbuff.X = info.srWindow.Right - info.srWindow.Left + 1;
        outbuff.Y = info.srWindow.Bottom - info.srWindow.Top + 1;
        SetConsoleScreenBufferSize(hConsole, outbuff);
    }

    
    
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
