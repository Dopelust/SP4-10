#include "Transform.h"
#include "../Entity.h"

Transform::Transform() : parent(NULL), position(0,0,0), rotation(0,0,0), size(1, 1, 1)
{
}

Transform::~Transform()
{
}

void Transform::Init(Entity * root)
{
	if (root->parent)
		parent = root->parent->GetComponent<Transform>();
}

Mtx44 Transform::T()
{
	Mtx44 T;
	T.SetToTranslation(position.x, position.y, position.z);
	return T;
}

Mtx44 Transform::R()
{
	Mtx44 Rx, Ry, Rz;
	Rx.SetToRotation(rotation.x, 1, 0, 0);
	Ry.SetToRotation(rotation.y, 0, 1, 0);
	Rz.SetToRotation(rotation.z, 0, 0, 1);

	if (!origin.IsZero())
	{
		Mtx44 T1, T2;
		T1.SetToTranslation(origin.x, origin.y, origin.z);
		T2.SetToTranslation(-origin.x, -origin.y, -origin.z);

		return T1 * Rx * Ry * Rz * T2;
	}
	
	return Rx * Ry * Rz;
}

Mtx44 Transform::S()
{
	Mtx44 S;
	S.SetToScale(size.x, size.y, size.z);
	return S;
}

Mtx44 Transform::GetTransformation()
{
	return T() * R() * S();
}

Vector3 Transform::GetPosition()
{
	Vector3 position = this->position;

	if (parent)
		position += parent->GetPosition();

	return position;
}

Vector3 Transform::GetSize()
{
	return size;
}

Vector3 Transform::GetRotation()
{
	Vector3 rotation = this->rotation;

	if (parent)
		rotation += parent->GetRotation();

	return rotation;
}

void Transform::SetPosition(float x, float y, float z)
{
	position.Set(x, y, z);
}

void Transform::SetRotation(float x, float y, float z)
{
	rotation.Set(x, y, z);
}

void Transform::SetSize(float xyz)
{
	size.Set(xyz, xyz, xyz);
}

void Transform::SetSize(float x, float y, float z)
{
	size.Set(x, y, z);
}

void Transform::SetOrigin(float x, float y, float z)
{
	origin.Set(x, y, z);
}

Vector3 & Transform::Position()
{
	return position;
}

Vector3 & Transform::Rotation()
{
	return rotation;
}

Vector3 & Transform::Size()
{
	return size;
}
