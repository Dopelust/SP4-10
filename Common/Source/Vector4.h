#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector3.h"

struct Vector4
{
public:
	Vector4(float x = 0, float y = 0, float z = 0, float w = 1);
	Vector4(Vector3 xyz, float w = 1);

	void Set(float x = 0, float y = 0, float z = 0, float w = 1);

	void operator= (Vector3& rhs);
	void operator* (float& scalar);
	Vector4 operator* (const Vector4& rhs);

	friend std::ostream& operator<<(std::ostream& os, Vector4& rhs); //print to ostream

	float x;
	float y;
	float z;
	float w;
};
#endif