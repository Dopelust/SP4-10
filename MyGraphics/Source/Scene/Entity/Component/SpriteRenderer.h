#pragma once

#include "Component.h"
#include "Vector4.h"

class Mesh2D;
class Sprite;
class SpriteRenderer : public Component
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void SetAlignCenter(bool alignCenter);
	void SetLayer(int layer);

	void SetSprite(Sprite* sprite);
	Vector4 color;

protected:
	Sprite* sprite;

	int layer;
	bool alignCenter;

	void Update(double dt);
	void Draw(const Mtx44& parent);
};