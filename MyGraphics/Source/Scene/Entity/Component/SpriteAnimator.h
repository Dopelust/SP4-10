#pragma once

#include "Component.h"

class Sprite;
class SpriteRenderer;
class Animation;
class Animator;
class SpriteAnimator : public Component
{
public:
	SpriteAnimator();
	~SpriteAnimator();

	bool IsEnded();

	void Init(Entity* ent);
	void Update(double dt);
	void SetAnimator(Animator* anim);
	
	void Play(const char* name, bool loop = true);

protected:
	Sprite* GetFrame();

	Animator* anim;
	Animation* current;

	float frameTimer;
	bool ended;
	bool loop;

	SpriteRenderer* sprite;
};