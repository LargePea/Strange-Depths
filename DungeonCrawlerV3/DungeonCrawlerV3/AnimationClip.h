#pragma once

#include "Image.h"
#include <map>

class AnimationClip {
private:
	bool _exitTime;
	bool _isLooping;

	std::map<int, Image> _timeLine;
	int _maxFrameCount;

public:
	AnimationClip(std::initializer_list<std::pair<int, Image>> keyframes, bool hasExitTime = true, bool isLooping = true);
	AnimationClip(const char* keyframes, bool hasExitTime = true, bool isLooping = true);

	inline const Image* GetFrame(int frameCount) const
	{
		auto frame = _timeLine.find(frameCount);
		if (frame == _timeLine.end()) return nullptr;
		return &frame->second;
	}

	inline const int& GetClipFrameCount() const { return _maxFrameCount; }

	inline const bool& GetExitTime() const { return _exitTime; }
	
	inline const bool& GetLooping() const { return _isLooping; }
};