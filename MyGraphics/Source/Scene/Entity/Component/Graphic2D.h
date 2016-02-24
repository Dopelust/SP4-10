#pragma once

#include "Component.h"
#include "Vector4.h"

class Texture;
class Graphic2D : public Component
{
public:
	Graphic2D();
	~Graphic2D();

	void SetAlignCenter(bool alignCenter);

	void SetLayer(int layer);
	void SetTexture(Texture* texture);

	void SetUV(float u1, float v1, float u2, float v2);
	void SetUVMin(float u, float v);
	void SetUVMax(float u, float v);

	void SetColor(float r, float g, float b, float a = 1);
	Vector4& GetColor();

protected:
	Texture* texture;
	Vector4 uv;
	Vector4 color;
	int layer;
	bool alignCenter;

	void Draw(const Mtx44& parent);
};