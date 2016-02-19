#include "Sprite.h"

Sprite::Sprite() : texture(NULL), uv(0, 0, 1, 1)
{
}

Sprite::~Sprite()
{
}

void Sprite::SetUV(Vector4 uv)
{
	this->uv = uv;
}

void Sprite::SetTexture(Texture * texture)
{
	this->texture = texture;
}

Vector4 Sprite::GetUV()
{
	return uv;
}

Texture * Sprite::GetTexture()
{
	return texture;
}
