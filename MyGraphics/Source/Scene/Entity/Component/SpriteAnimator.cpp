#include "SpriteAnimator.h"
#include "SpriteRenderer.h"
#include "../../../Animator.h"
#include "../../../Animation.h"
#include "../Entity.h"

SpriteAnimator::SpriteAnimator() : frameTimer(0), current(NULL), loop(true), ended(false)
{
}

SpriteAnimator::~SpriteAnimator()
{
}

bool SpriteAnimator::IsEnded()
{
	return ended;
}

void SpriteAnimator::SetAnimator(Animator * anim)
{
	this->anim = anim;
}

void SpriteAnimator::Init(Entity * ent)
{
	sprite = ent->GetComponent<SpriteRenderer>();
}

void SpriteAnimator::Update(double dt)
{
	if (ended)
		return;

	if (current)
	{
		frameTimer += dt;

		if (frameTimer > current->GetAnimationTime())
		{
			frameTimer = 0;
			
			if (!loop)
			{
				ended = true;
				return;
			}
		}
	}

	sprite->SetSprite(GetFrame());
}

void SpriteAnimator::Play(const char * name, bool loop)
{
	current = anim->GetAnimation(name);
	frameTimer = 0;
	ended = false;
	this->loop = loop;

	sprite->SetSprite(GetFrame());
}

Sprite * SpriteAnimator::GetFrame()
{
	if (current)
		return current->GetFrame(frameTimer);

	return NULL;
}