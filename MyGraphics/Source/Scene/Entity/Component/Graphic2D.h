#pragma once

#include "Component.h"
#include "Vector4.h"

class Texture;

class Graphic2D : public Component
{
public:
	Graphic2D();
	~Graphic2D();

	Texture* texture;
	Vector4 color;

	void SetAlignCenter(bool alignCenter);
	void SetLayer(int layer);

protected:
	int layer;
	bool alignCenter;

	virtual void Draw(const Mtx44& parent);
};