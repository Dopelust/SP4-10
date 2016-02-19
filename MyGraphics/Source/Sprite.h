#ifndef SPRITE_H
#define SPRITE_H

#include "Vector4.h"

#include <vector>
using namespace::std;

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
private:
	Texture* texture;
	Vector4 uv;
};

#endif