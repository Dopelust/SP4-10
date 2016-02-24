#include "Graphic2D.h"
#include "../../../Mesh2D.h"

void Graphic2D::SetLayer(int layer)
{
	this->layer = layer;
}

void Graphic2D::SetTexture(Texture * texture)
{
	this->texture = texture;
}

void Graphic2D::SetUV(float u1, float v1, float u2, float v2)
{
	uv.Set(u1, v1, u2, v2);
}

void Graphic2D::SetUVMin(float u, float v)
{
	uv.x = u;
	uv.y = v;
}

void Graphic2D::SetUVMax(float u, float v)
{
	uv.z = u;
	uv.w = v;
}

void Graphic2D::SetColor(float r, float g, float b, float a)
{
	color.Set(r, g, b, a);
}

Vector4& Graphic2D::GetColor()
{
	return color;
}

Graphic2D::Graphic2D() : texture(NULL), color(1,1,1,1), uv(0, 0, 1, 1), layer(0), alignCenter(true)
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

	Quad.GetInstance(texture, layer).Add(parent * T, color, uv);
}
