#pragma once

#include "Image.h"
#include <Windows.h>
#include <mutex>
#include <utility>
#include <array>
#include <vector>

#define SCREEN_HEIGHT 50
#define SCREEN_WIDTH 117
#define ORIGIN_HORIZONTAL_OFFSET 2
#define RENDER_UPDATES_PER_SECOND 15

class Screen 
{
private:
	static HANDLE _screenHandle;
	static COORD _currentCusorPosition;

	static std::array<char, SCREEN_HEIGHT* SCREEN_WIDTH> _bufferFrame;
	static std::mutex _bufferUpdateLock;

	static std::vector<const Image*> _imagesToRender;

public:
	static void Init(int screenWidth = SCREEN_HEIGHT, int screenHeight = SCREEN_WIDTH);

	static HANDLE GetScreenHandler();

	static void ResetCursor();

	static void MoveCursor(int x, int y);

	static void Renderer();

	static void AddImages(std::initializer_list<const Image*> images);

	static void RemoveImages(std::initializer_list<const Image*> images);

	static void ClearImages(bool updateScreen = true);

private:
	static void UpdateBuffer();

	static void CreateScreen(int& screenWidth, int& screenHeight);

	static void HideCursor();

	Screen() {};
};
