#include "SpriteRenderer.h"
#include "../../../Mesh2D.h"
#include "../../../Sprite.h"

SpriteRenderer::SpriteRenderer() : sprite(NULL)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::SetSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void SpriteRenderer::Draw(const Mtx44 & parent)
{
	if (sprite)
	{
		Mtx44 T;

		if (alignCenter)
			T.SetToTranslation(-0.5f, -0.5f, 0);
		else
			T.SetToIdentity();

		Quad.GetInstance(sprite->GetTexture(), layer).Add(parent * T, color, sprite->GetUV());
	}
}
