#pragma once

#include "Graphic2D.h"

class Sprite;
class SpriteRenderer : public Graphic2D
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void SetSprite(Sprite* sprite);

protected:
	Sprite* sprite;
	void Draw(const Mtx44& parent);
};