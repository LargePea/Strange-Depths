#pragma once

#include <Windows.h>

#define SCREEN_HEIGHT 50
#define SCREEN_WIDTH 115

class Screen 
{
private:
	static HANDLE _screenHandle;
	static COORD _currentCusorPosition;

public:
	static void Init(int screenWidth = SCREEN_HEIGHT, int screenHeight = SCREEN_WIDTH);

	static HANDLE GetScreenHandler();

	static void ResetCursor();

	static void MoveCursor(int x, int y);

	static void PrintMainMenu();


private:
	static void CreateScreen(int& screenWidth, int& screenHeight);

	Screen() {};
};