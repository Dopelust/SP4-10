#include "Spritesheet.h"
#include "Sprite.h"

Spritesheet::Spritesheet()
{
}

Spritesheet::~Spritesheet()
{
}

Sprite * Spritesheet::AddSprite()
{
	this->sprite.push_back(Sprite());
	return &sprite.back();
}

Sprite * Spritesheet::GetSprite(int i)
{
	if (i < sprite.size())
		return &sprite[i];

	return NULL;
}
