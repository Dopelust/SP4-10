#include "DrawInstance2D.h"
#include "Mesh2D.h"

DrawInstance2D::DrawInstance2D()
{
}

DrawInstance2D::DrawInstance2D(const Mtx44 & mtx, const Vector3 & color, const Vector4 & tex)
{
	Add(mtx, color, tex);
}

void DrawInstance2D::Bind(Mesh2D * mesh) const
{
	int numInstance = NumInstance();

	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer[Mesh2D::TEXTURE_OFFSET_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4) * numInstance, &textureOffset[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer[Mesh2D::COLOR_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4) * numInstance, &color[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer[Mesh2D::MODEL_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Mtx44) * numInstance, &modelMatrix[0], GL_DYNAMIC_DRAW);
}

void DrawInstance2D::Prepare(int numInstances)
{
	Clear();
	modelMatrix.reserve(numInstances);
	textureOffset.reserve(numInstances);
	color.reserve(numInstances);
}

void DrawInstance2D::Add(const Mtx44 & mtx, const Vector3 & color, const Vector4 & tex)
{
	modelMatrix.push_back(mtx);
	this->color.push_back(Vector4(color, 1));
	textureOffset.push_back(tex);
}

void DrawInstance2D::Add(const Mtx44 & mtx, const Vector4 & color, const Vector4 & tex)
{
	modelMatrix.push_back(mtx);
	this->color.push_back(color);
	textureOffset.push_back(tex);
}

void DrawInstance2D::Clear()
{
	modelMatrix.clear();
	textureOffset.clear();
	color.clear();
}

unsigned DrawInstance2D::NumInstance() const
{
	return modelMatrix.size();
}