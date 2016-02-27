#include "Vector3.h"
#include "MyMath.h"

Vector3::Vector3(float a, float b, float c) : x(a), y(b), z(c)
{
}

Vector3::Vector3(const Vector3 &rhs) : x(rhs.x), y(rhs.y), z(rhs.z)
{
}

Vector3::~Vector3()
{
}

void Vector3::Set(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

void Vector3::SetZero(void)
{
	x = y = z = 0;
}

bool Vector3::IsZero(void) const
{
	return Math::IsEqual(x, 0.f) && Math::IsEqual(y, 0.f) && Math::IsEqual(z, 0.f);
}


Vector3 Vector3::operator+(const Vector3& rhs) const
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& rhs) const
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector3 Vector3::operator-(void) const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(const Vector3& rhs) const
{
	return Vector3(rhs.x * x, rhs.y * y, rhs.z * z);
}

Vector3 Vector3::operator*(float scalar) const
{
	return Vector3(scalar * x, scalar * y, scalar * z);
}

Vector3& Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector3 Vector3::operator/(float scalar) const
{
	return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3& Vector3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

bool Vector3::operator<(const Vector3& rhs) const
{
	if (z < rhs.z)
	{
		return true;
	}
	else if (z == rhs.z)
	{
		if (y < rhs.y)
		{
			// z == b.z and y < b.y
			return true;
		}
		else if (y == rhs.y)
		{
			if (x < rhs.x)
			{
				return true;
			}
			else if (x == rhs.x)
			{
				// completely equal
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			// z==b.z and y >= b.y
			return false;
		}
	}
	else
	{
		// z >= b.z
		return false;
	}
}

bool Vector3::operator==(const Vector3& rhs) const
{
	return Math::IsEqual(x, rhs.x) && Math::IsEqual(y, rhs.y) && Math::IsEqual(z, rhs.z);
}

bool Vector3::operator!= (const Vector3& rhs) const
{
	return !Math::IsEqual(x, rhs.x) || !Math::IsEqual(y, rhs.y) || !Math::IsEqual(z, rhs.z);
}

Vector3& Vector3::operator=(const Vector3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

float Vector3::Length(void) const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::LengthSquared(void) const
{
	return x * x + y * y + z * z;
}

float Vector3::Dot(const Vector3& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3 Vector3::Cross(const Vector3& rhs) const
{
	return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

float Q_rsqrt(float number)
{
	long i;
	float x2, y;

	x2 = number * 0.5F;
	y = number;
	i = *(long *)&y;                      
	i = 0x5f3759df - (i >> 1);               
	y = *(float *)&i;
	y = y * (1.5F - (x2 * y * y)); 

	return y * (1.5F - (x2 * y * y));
}

Vector3 Vector3::Normalized(void) const
{
	float d = Length();

	if (d <= Math::EPSILON && -d <= Math::EPSILON)
		return Vector3(x, y, z);

	return Vector3(x / d, y / d, z / d);

	//float d = LengthSquared();

	//if (d <= Math::EPSILON && -d <= Math::EPSILON)
	//	return Vector3(x, y, z);

	//float inv = Q_rsqrt(d);
	//return Vector3(x / d, y / d, z / d);
}

Vector3& Vector3::Normalize(void)
{
	float d = Length();

	if (d <= Math::EPSILON && -d <= Math::EPSILON)
		return *this;

	x /= d;
	y /= d;
	z /= d;
	return *this;

	//float d = LengthSquared();

	//if (d <= Math::EPSILON && -d <= Math::EPSILON)
	//	return *this;

	//float inv = Q_rsqrt(d);
	//x *= inv;
	//y *= inv;
	//z *= inv;
	//return *this;
}

Vector3& Vector3::Rotate(float angle, Vector3 axis)
{
	float sinHalfAngle = sin(Math::DegreeToRadian(angle * 0.5f));
	float cosHalfAngle = cos(Math::DegreeToRadian(angle * 0.5f));

	float rX = axis.x * sinHalfAngle;
	float rY = axis.y * sinHalfAngle;
	float rZ = axis.z * sinHalfAngle;
	float rW = cosHalfAngle;

	return *this;
}

std::ostream& operator<< (std::ostream& os, const Vector3& rhs)
{
	os << rhs.x << ", " << rhs.y << ", " << rhs.z;
	return os;
}

Vector3 operator*(float scalar, const Vector3& rhs)
{
	return rhs * scalar;
}

float Vector3::Dist(const Vector3& rhs) const
{
	return sqrt(((x - rhs.x)*(x - rhs.x)) + ((y - rhs.y)*(y - rhs.y)) + ((z - rhs.z)*(z - rhs.z)));
}

float Vector3::DistSquared(const Vector3& rhs) const
{
	return ((x - rhs.x)*(x - rhs.x)) + ((y - rhs.y)*(y - rhs.y)) + ((z - rhs.z)*(z - rhs.z));
}

Vector3& Vector3::SphericalToCartesian(float yaw, float pitch)
{
	x = cos(Math::DegreeToRadian(pitch)) * sin(Math::DegreeToRadian(yaw));
	y = sin(Math::DegreeToRadian(pitch));
	z = cos(Math::DegreeToRadian(pitch)) * cos(Math::DegreeToRadian(yaw));

	return *this;
}

#include "Vector2.h"

Vector2 Vector3::GetVector2()
{
	return Vector2(x, y);
}
