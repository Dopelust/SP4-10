#include "Animator.h"

Animator::Animator() 
{
}

Animator::~Animator()
{
}

#include <iostream>
void Animator::AddAnimation(const char * name, Animation * anim)
{
	animation[name] = anim;
}

Animation * Animator::GetAnimation(const char * name)
{
	if (animation.find(name) != animation.end())
	{
		return animation[name];
	}

	return NULL;
}
