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

#include "Mesh2D.h"

void Sprite::Render(const Mtx44 & mtx, const Vector4& color, int layer)
{
	Quad.GetInstance(GetTexture(), layer).Add(mtx, color, GetUV());
}
