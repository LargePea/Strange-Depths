#pragma once

#include "Image.h"
#include "AnimationClip.h"
#include "AnimatorCondition.h"
#include <thread>
#include <vector>
#include <map>

#define ANIMATION_FRAMES_PER_SECOND 15

class Animator {
private:
	std::vector<AnimationClip> _animationClips;

	std::map<const AnimationClip*, std::vector<AnimatorCondition*>> _transitionConditions;

	bool _animatorIsRunning = false;

	const AnimationClip* _currentAnimation;
	Image* _imageToUpdate;
	std::thread _animationThread;

	int _updateLoop = 1000 / ANIMATION_FRAMES_PER_SECOND;

protected:
	std::map<const char*, bool> _boolConditions;
	std::map<const char*, bool> _triggerConditions;

private:
	void AnimationLoop();

	void AddConditions(AnimationClip* origin, std::initializer_list<AnimatorCondition*> conditions);

	void CheckCurrentAnimationConditions();

public:
	Animator(std::initializer_list<AnimationClip> clips, Image* imageToUpdate);

	~Animator();

	inline void SetBool(const char* name, bool newValue) { if (_boolConditions.find(name) != _boolConditions.end()) _boolConditions[name] = newValue; }

	inline void SetTrigger(const char* name, bool newValue) { if (_triggerConditions.find(name) != _triggerConditions.end()) _triggerConditions[name] = newValue; }

	inline void ActivateAnimator() { 
		_animatorIsRunning = true;
		_animationThread = std::thread(&Animator::AnimationLoop, this);
		_animationThread.detach();
	}

	inline void DeactivateAnimator() { _animatorIsRunning = false; }

	inline float GetCurrentClipLength() { return (float)_currentAnimation->GetClipFrameCount() / ANIMATION_FRAMES_PER_SECOND; }

};