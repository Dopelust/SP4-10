#include "SpriteRenderer.h"
#include "../../../Mesh2D.h"
#include "../../../Sprite.h"

SpriteRenderer::SpriteRenderer() : color(1, 1, 1, 1)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::SetSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void SpriteRenderer::SetColor(float r, float g, float b, float a)
{
	color.Set(r, g, b, a);
}

void SpriteRenderer::Update(double dt)
{
}

void SpriteRenderer::Draw(const Mtx44 & parent)
{
	Mtx44 T;
	T.SetToTranslation(-0.5f, -0.5f, 0);

	Quad.GetInstance(sprite->GetTexture()).Add(parent * T, color, sprite->GetUV());
}
