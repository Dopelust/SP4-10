#include "Instance.h"
#include "Mesh.h"

DrawInstance::DrawInstance()
{
}

DrawInstance::DrawInstance(const Mtx44 & mtx, const Vector3 & color, const Vector2 & tex)
{
	Add(mtx, color, tex);
}

void DrawInstance::Bind(Mesh * mesh) const
{
	int numInstance = NumInstance();

	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer[Mesh::TEXTURE_OFFSET_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * numInstance, &textureOffset[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer[Mesh::COLOR_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4) * numInstance, &color[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer[Mesh::MODEL_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Mtx44) * numInstance, &modelMatrix[0], GL_DYNAMIC_DRAW);
}

void DrawInstance::Prepare(int numInstances)
{
	Clear();
	modelMatrix.reserve(numInstances);
	textureOffset.reserve(numInstances);
	color.reserve(numInstances);
}

void DrawInstance::Add(const Mtx44 & mtx, const Vector3 & color, const Vector2 & tex)
{
	modelMatrix.push_back(mtx);
	this->color.push_back(Vector4(color, 1));
	textureOffset.push_back(tex);
}

void DrawInstance::Add(const Mtx44 & mtx, const Vector4 & color, const Vector2 & tex)
{
	modelMatrix.push_back(mtx);
	this->color.push_back(color);
	textureOffset.push_back(tex);
}

void DrawInstance::Clear()
{
	modelMatrix.clear();
	textureOffset.clear();
	color.clear();
}

unsigned DrawInstance::NumInstance() const
{
	return modelMatrix.size();
}