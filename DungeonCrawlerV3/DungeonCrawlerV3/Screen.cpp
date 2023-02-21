#include "Screen.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

HANDLE Screen::_screenHandle;
COORD Screen::_currentCusorPosition;
bool Screen::_updateScreen;
std::mutex Screen::_bufferUpdateLock;
std::array<char, SCREEN_HEIGHT* SCREEN_WIDTH> Screen::_bufferFrame;
std::vector<Image*> Screen::_imagesToRender;


void Screen::Init(int screenWidth, int screenHeight) {
	_screenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	_currentCusorPosition.X = 0;
	_currentCusorPosition.Y = 0;
    CreateScreen(screenWidth, screenHeight);
    HideCursor();

    std::thread(Screen::Renderer).detach(); // begin rendering loop
}

void Screen::Renderer() {
    int updateSpeed = 1000 / RENDER_UPDATES_PER_SECOND;

    while (true)
    {
        _bufferUpdateLock.lock();
        UpdateBuffer();
        std::cout << std::flush; //flush buffer just incase it wasnt due to a crash
        ResetCursor();

        for (int row = 0; row < SCREEN_HEIGHT; ++row) {
            char line[SCREEN_WIDTH + 1]{};
            for (int character = 0; character < SCREEN_WIDTH; ++character) {
                line[character] = _bufferFrame[character + row * SCREEN_WIDTH];
            }
            line[SCREEN_WIDTH] = '\0';
            std::cout << line;
            if (!(row == SCREEN_HEIGHT - 1)) std::cout << "\n";
        }
        _updateScreen = false;
        std::cout << std::flush;
        _bufferUpdateLock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(updateSpeed));
    }
}

HANDLE Screen::GetScreenHandler() {
	return _screenHandle;
}

void Screen::CreateScreen(int& screenWidth, int& screenHeight) {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 970, 840, TRUE);

    COORD outbuff;
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(GetScreenHandler(), &scrBufferInfo);
    outbuff.X = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
    outbuff.Y = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
    SetConsoleScreenBufferSize(GetScreenHandler(), outbuff);

}

void Screen::HideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(GetScreenHandler(), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetScreenHandler(), &cursorInfo);
}

void Screen::ResetCursor() {
	MoveCursor(0, 0);
}

void Screen::MoveCursor(int x, int y) {
	_currentCusorPosition.X = x;
	_currentCusorPosition.Y = y;
	SetConsoleCursorPosition(_screenHandle, _currentCusorPosition);
}

void Screen::AddImages(std::initializer_list<Image*> images, bool updateScreen) {
    _bufferUpdateLock.lock();
    for (auto& image : images) {
        _imagesToRender.push_back(image);
    }
    _bufferUpdateLock.unlock();
}

void Screen::RemoveImages(std::initializer_list<Image*> images, bool updateScreen) {
    _bufferUpdateLock.lock();
    for (auto& image : images) {
        for (auto it = _imagesToRender.begin(); it != _imagesToRender.end(); ++it) {
            if (image == *it) {
                _imagesToRender.erase(it);
                break;
            }
        }
    }
    _bufferUpdateLock.unlock();
}

void Screen::ClearImages(bool updateScreen) {
    _bufferUpdateLock.lock();
    _imagesToRender.clear();
    _bufferUpdateLock.unlock();
}

void Screen::UpdateBuffer() {
    _bufferFrame.fill(' ');
    std::sort(_imagesToRender.begin(), _imagesToRender.end());
    _updateScreen = true;

    for (const Image* image : _imagesToRender) {
        const std::array<std::string, MAX_IMAGE_HEIGHT> imageToLoad = image->GetImage();
        const std::pair<int, int> startingCoords = image->GetDisplayPosition();

        for (int row = 0; row < imageToLoad.size(); ++row) {
            if (startingCoords.second + row == SCREEN_HEIGHT) break; //stop rendering image if it's off the bottom of the screen
            for (int character = 0; character < imageToLoad[row].size(); ++character) {
                if (startingCoords.first + character == SCREEN_WIDTH) break; //stop processing line if it's off the screen

                char possiblePixel = imageToLoad[row][character];
                if (possiblePixel == ' ') continue; //To display transparency, dont render pixels that are "transparent"
                if (possiblePixel == '.') possiblePixel = ' ';

                _bufferFrame[(startingCoords.first + character + ORIGIN_HORIZONTAL_OFFSET) + (SCREEN_WIDTH * (row + startingCoords.second))] = possiblePixel;
            }
        }
    }
}