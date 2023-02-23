#include "Animator.h"
#include <chrono>

Animator::Animator(std::initializer_list<AnimationClip> clips, Image* imageToUpdate) 
	: _imageToUpdate(imageToUpdate) {
	_animationClips.reserve(clips.size());
	for (auto& clip : clips) {
		_animationClips.push_back(clip);
	}

	_currentAnimation = &(_animationClips[0]);
}

Animator::~Animator() {
	if (_animatorIsRunning)
	{
		DeactivateAnimator();
		std::this_thread::sleep_for(std::chrono::milliseconds(_updateLoop));
	}

	for (auto clip : _transitionConditions) {
		for (auto condition : clip.second) {
			delete condition;
		}
	}
}

void Animator::AnimationLoop() {	
	int frame = 1;
	while (_animatorIsRunning)
	{
		//if animation does not have exit time check conditions
		if (!_currentAnimation->GetExitTime()) {
			CheckCurrentAnimationConditions();
		}

		//if animation is looping dont bother with loading final frame, just reset animator
		if (frame == _currentAnimation->GetClipFrameCount()) {
			if(_currentAnimation->GetLooping()) frame = 1;
			CheckCurrentAnimationConditions();
		}

		//only update frames if there are still key frames to update
		if (frame <= _currentAnimation->GetClipFrameCount()) {
			const Image* retrievedFrame = _currentAnimation->GetFrame(frame);
			if (retrievedFrame != nullptr) *_imageToUpdate = std::move(*retrievedFrame); //change frame if there is a new keyframe

			++frame;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(_updateLoop));
	}
}

void Animator::AddConditions(AnimationClip* origin, std::initializer_list<AnimatorCondition*> conditions) {
	_transitionConditions[origin].reserve(conditions.size());
	for (auto& condition : conditions) {
		_transitionConditions[origin].emplace_back(condition);
	}
}

void Animator::CheckCurrentAnimationConditions() {
	for (const AnimatorCondition* condition : _transitionConditions[_currentAnimation])
		if (condition->CheckCondition()) 
			_currentAnimation = condition->GetTargetClip();
}