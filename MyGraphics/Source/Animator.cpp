#include "Animator.h"
#include "Animation.h"
#include "Sprite.h"

Sprite * Animator::GetFrame()
{
	return active->GetFrame(frameTimer);
}

void Animator::Play(const char * name)
{
	if (animation.find(name) != animation.end())
	{
		active = animation[name];
		frameTimer = 0;
	}
}

void Animator::Update(float dt)
{
	frameTimer += dt;
	
	if (frameTimer > active->GetAnimationTime())
		frameTimer = 0;
}

Animator::Animator() : frameTimer(0), active(NULL)
{
}

Animator::~Animator()
{
}

void Animator::AddAnimation(const char * name, Animation * anim)
{
	animation[name] = anim;
	active = anim;
}

Animation * Animator::GetAnimation(const char * name)
{
	if (animation.find(name) != animation.end())
	{
		return animation[name];
	}

	return NULL;
}
