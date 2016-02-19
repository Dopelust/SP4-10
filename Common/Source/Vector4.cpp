#include "Vector4.h"

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

Vector4::Vector4(Vector3 xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w)
{
}

void Vector4::Set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Vector4::operator=(Vector3& rhs)
{
	Set(rhs.x, rhs.y, rhs.z);
}

void Vector4::operator*(float& scalar)
{
	Set(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vector4 Vector4::operator*(const Vector4 & rhs)
{
	return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

std::ostream& operator<< (std::ostream& os, Vector4& rhs)
{
	os << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w;
	return os;
}
