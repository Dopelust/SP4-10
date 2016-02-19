#pragma once

#include "Component.h"
#include "Vector3.h"

class Transform : public Component
{
public:
	Transform();
	~Transform();

	void Init(Entity* root);

	Mtx44 T();
	Mtx44 R();
	Mtx44 S();
	Mtx44 GetTransformation();

	Vector3 GetPosition();
	Vector3 GetSize();
	Vector3 GetRotation();

	void SetPosition(float x, float y, float z = 0);
	void SetRotation(float x = 0, float y = 0, float z = 0);
	void SetSize(float xyz);
	void SetSize(float x, float y, float z = 1);
	
	void SetOrigin(float x, float y, float z = 0);

	Vector3& Position();
	Vector3& Rotation();
	Vector3& Size();

private:
	Vector3 position;
	Vector3 rotation;
	Vector3 origin;
	Vector3 size;

	Transform* parent;
};