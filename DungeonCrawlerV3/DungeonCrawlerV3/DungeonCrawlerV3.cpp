#include "Screen.h"
#include "Image.h"
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <array>
#include "Player.h"
#include "Enemy.h"
#include "Inventory.h"
#include "InventoryMenu.h"
#include "Item.h"
#include "EventSystem.h"
#include <functional>
#include <string>
#include "Buff.h"

std::vector<Enemy> vectorTest;

void TestCopy(Enemy &enemy) {
    vectorTest.push_back(enemy);
};

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

    Screen::PrintMainMenu();

    std::cout << "\033[" << 2 << ";" << 3 << "f";
    std::cin.get();
    std::array<std::string, MAX_IMAGE_HEIGHT> test = { "test", "image" };
    std::array<int, 2> testPos = std::array<int, 2> {0, 0};
    Image image(test, 10, testPos);

    std::cout << (*image.GetImage())[0] << "\n";
    test[0] = "updated";
    std::cout << (*image.GetImage())[0] << "\n";
    std::cout << image.GetPriority() << "\n";

    //Player player;
    //Enemy enemy;
    //float testAttack = 2.0f;
    //enemy.Damage(testAttack);
    //std::cout << enemy.GetCurrentHealth();
    GameState::SetStateMask(GameStateMask::Combat);
    int state = GameState::GetStateMask();
    Character character;
    LifeSteal* lsBuff = new LifeSteal(&character, 1, 0.5f);
    state = GameState::GetStateMask();
    Item item1("item1", 2);
    std::cout << item1.GetName() << std::endl;
    character.Attack(character);
}
