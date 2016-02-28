#ifndef SPRITE_H
#define SPRITE_H

#include "Vector4.h"

#include <vector>
using namespace::std;

class Mtx44;
class Texture;

class Sprite
{
public:
	Sprite();
	~Sprite();

	void SetUV(Vector4 uv);
	void SetTexture(Texture* texture);

	Vector4 GetUV();
	Texture* GetTexture();

	void Render(const Mtx44& mtx, const Vector4& color, int layer);
private:
	Texture* texture;
	Vector4 uv;
};

#endif