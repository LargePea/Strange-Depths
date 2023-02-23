#include "AnimationClip.h"

AnimationClip::AnimationClip(std::initializer_list<std::pair<int, Image>> keyframes, bool hasExitTime, bool isLooping) 
	: _exitTime(hasExitTime), _isLooping(isLooping), _maxFrameCount(0) {
	for (auto& keyframe : keyframes) {
		_timeLine.emplace(keyframe.first, keyframe.second);
		if (_maxFrameCount < keyframe.first) _maxFrameCount = keyframe.first;
	}
}