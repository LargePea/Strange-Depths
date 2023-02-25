#include "AnimationClip.h"
#include <fstream>
#include <sstream>

AnimationClip::AnimationClip(std::initializer_list<std::pair<int, Image>> keyframes, bool hasExitTime, bool isLooping) 
	: _exitTime(hasExitTime), _isLooping(isLooping), _maxFrameCount(0) {
	for (auto& keyframe : keyframes) {
		_timeLine.emplace(keyframe.first, keyframe.second);
		if (_maxFrameCount < keyframe.first) _maxFrameCount = keyframe.first;
	}
}

AnimationClip::AnimationClip(const char* keyFramesFilePath, bool hasExitTime, bool isLooping)
	: _exitTime(hasExitTime), _isLooping(isLooping), _maxFrameCount(0) {

	if (std::ifstream file{ keyFramesFilePath }) {
		std::string line, frame, filePath, priority, xCoord, yCoord;
		while (std::getline(file, line)) {
			std::istringstream params(line);
			params >> frame >> filePath >> priority >> xCoord >> yCoord;
			int iFrame = std::stoi(frame); //cache so we dont have to convert three times
			_timeLine.emplace(iFrame, Image{ filePath, std::stoi(priority), {std::stoi(xCoord), std::stoi(yCoord)} });
			if (_maxFrameCount < iFrame) _maxFrameCount = iFrame;
		}
		file.close();
	}
}