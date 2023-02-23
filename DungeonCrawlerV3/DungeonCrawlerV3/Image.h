#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <utility>

class Image {
protected:
	std::vector<std::string> _image;

private:
	int _priority = 0;
	std::pair<int, int> _displayPosition;

public:
	Image(const char* imageFilePath, int priority, std::pair<int, int> displayPos);

	Image(std::vector<std::string> image, int priority, std::pair<int, int> displayPos);

	Image(const Image&);
	Image& operator=(const Image& other);

	Image(Image&&) noexcept;
	Image& operator=(Image&&) noexcept;

	//Getters
	inline const std::vector<std::string>& GetImage() const { return _image; }

	inline size_t GetPriority() { return _priority; }

	inline const std::pair<int, int>& GetDisplayPosition() const { return _displayPosition; }

	static bool ComparePointers(const Image* lhs, const Image* rhs);
	friend bool operator>(const Image& lhs, const Image& rhs);
	friend bool operator<(const Image& lhs, const Image& rhs);

	Image operator+(const Image& rhs);
};