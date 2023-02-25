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
	std::map<const AnimationClip*, std::vector<AnimatorCondition*>> _transitionConditions;

	bool _animatorIsRunning = false;
	bool _deactivatedAnimator = true;

	const AnimationClip* _currentAnimation;
	Image* _imageToUpdate;

	int _updateLoop = 1000 / ANIMATION_FRAMES_PER_SECOND;

	bool _transitionedClip = false;

protected:
	std::vector<AnimationClip> _animationClips;

	std::map<const char*, bool> _boolConditions;
	std::map<const char*, bool> _triggerConditions;

private:
	void AnimationLoop();

	bool CheckCurrentAnimationConditions();

protected:
	void AddConditions(AnimationClip* origin, std::initializer_list<AnimatorCondition*> conditions);

public:
	Animator(std::initializer_list<AnimationClip> clips, Image* imageToUpdate);

	~Animator();

	inline void SetBool(const char* name, bool newValue) { if (_boolConditions.find(name) != _boolConditions.end()) _boolConditions[name] = newValue; }

	inline void SetTrigger(const char* name) { if (_triggerConditions.find(name) != _triggerConditions.end()) 
		_triggerConditions[name] = true; }

	inline void ActivateAnimator() { 
		_animatorIsRunning = true;
		_deactivatedAnimator = false;
		std::thread(&Animator::AnimationLoop, this).detach();	
	}

	void WaitForNextClipCompletion();

	inline void DeactivateAnimator() { _animatorIsRunning = false; }

	inline float GetCurrentClipLength() { return (float)_currentAnimation->GetClipFrameCount() * 1000 / ANIMATION_FRAMES_PER_SECOND; }

};