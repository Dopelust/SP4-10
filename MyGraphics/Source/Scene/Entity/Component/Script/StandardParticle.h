#pragma once

#include "../Component.h"

class SpriteAnimator;

class StandardParticle : public Component
{
public:
	StandardParticle();
	~StandardParticle();

	void Init(Entity* ent);
	void Update(double dt);

private:
	Entity* owner;
	SpriteAnimator* anim;
};