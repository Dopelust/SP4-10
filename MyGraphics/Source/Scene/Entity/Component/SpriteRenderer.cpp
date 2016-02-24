#include "SpriteRenderer.h"
#include "../../../Mesh2D.h"
#include "../../../Sprite.h"

SpriteRenderer::SpriteRenderer() : color(1, 1, 1, 1), layer(0), alignCenter(true)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::SetAlignCenter(bool alignCenter)
{
	this->alignCenter = alignCenter;
}

void SpriteRenderer::SetLayer(int layer)
{
	this->layer = layer;
}

void SpriteRenderer::SetSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void SpriteRenderer::Update(double dt)
{
}

void SpriteRenderer::Draw(const Mtx44 & parent)
{
	Mtx44 T;

	if (alignCenter)
		T.SetToTranslation(-0.5f, -0.5f, 0);
	else
		T.SetToIdentity();

	Quad.GetInstance(sprite->GetTexture(), layer).Add(parent * T, color, sprite->GetUV());
}
