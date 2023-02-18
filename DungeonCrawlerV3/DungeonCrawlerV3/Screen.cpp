#include "Screen.h"
#include <iostream>

HANDLE Screen::_screenHandle;
COORD Screen::_currentCusorPosition;

void Screen::Init(int screenWidth, int screenHeight) {
	_screenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	_currentCusorPosition.X = 0;
	_currentCusorPosition.Y = 0;
    CreateScreen(screenWidth, screenHeight);
}

void Screen::CreateScreen(int& screenWidth, int& screenHeight) {
    COORD outbuff;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND window = GetConsoleWindow();
    CONSOLE_SCREEN_BUFFER_INFO info;
    SMALL_RECT windowSize = { 0, 0, screenWidth,  screenHeight};
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    if (GetConsoleScreenBufferInfo(hConsole, &info)) {
        outbuff.X = info.srWindow.Right - info.srWindow.Left + 1;
        outbuff.Y = info.srWindow.Bottom - info.srWindow.Top + 1;
        SetConsoleScreenBufferSize(hConsole, outbuff);
    }
}

HANDLE Screen::GetScreenHandler() {
	return _screenHandle;
}

void Screen::ResetCursor() {
	MoveCursor(0, 0);
}

void Screen::MoveCursor(int x, int y) {
	_currentCusorPosition.X = x;
	_currentCusorPosition.Y = y;
	SetConsoleCursorPosition(_screenHandle, _currentCusorPosition);
}


void Screen::PrintMainMenu() {
	std::cout << "Test, this runs\n";
}