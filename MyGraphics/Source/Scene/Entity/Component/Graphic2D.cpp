#include "Graphic2D.h"
#include "../../../Mesh2D.h"

void Graphic2D::SetLayer(int layer)
{
	this->layer = layer;
}

Graphic2D::Graphic2D() : color(1,1,1,1), layer(0), alignCenter(true), texture(NULL)
{
}

Graphic2D::~Graphic2D()
{
}

void Graphic2D::SetAlignCenter(bool alignCenter)
{
	this->alignCenter = alignCenter;
}

void Graphic2D::Draw(const Mtx44 & parent)
{
	Mtx44 T;

	if (alignCenter)
		T.SetToTranslation(-0.5f, -0.5f, 0);
	else
		T.SetToIdentity();

	Quad.GetInstance(texture, layer).Add(parent * T, color, Vector4(0, 0, 1, 1));
}
