#include "Vector2.h"
#include "MyMath.h"

Vector2::Vector2(float a, float b) : x(a), y(b)
{
}

Vector2::Vector2(const Vector2 &rhs) : x(rhs.x), y(rhs.y)
{
}

Vector2::~Vector2()
{
}

void Vector2::Set(const float &a, const float &b)
{
	x = a;
	y = b;
}

void Vector2::SetZero(void)
{
	x = y = 0;
}

bool Vector2::IsZero(void) const
{
	return Math::IsEqual(x, 0.f) && Math::IsEqual(y, 0.f);
}


Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2 Vector2::operator-(void) const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator*(const Vector2& rhs) const
{
	return Vector2(rhs.x * x, rhs.y * y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(scalar * x, scalar * y);
}

Vector2& Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

Vector2& Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

bool Vector2::operator==(const Vector2& rhs) const
{
	return Math::IsEqual(x, rhs.x) && Math::IsEqual(y, rhs.y);
}

bool Vector2::operator!= (const Vector2& rhs) const
{
	return !Math::IsEqual(x, rhs.x) || !Math::IsEqual(y, rhs.y);
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

float Vector2::Length(void) const
{
	return sqrt(x * x + y * y);
}

float Vector2::LengthSquared(void) const
{
	return x * x + y * y;
}

float Vector2::Dot(const Vector2& rhs) const
{
	return x * rhs.x + y * rhs.y;
}

Vector2 Vector2::Cross() const
{
	return Vector2(y, -x);
}

Vector2 & Vector2::Rotate(float w)
{
	x = cos(Math::DegreeToRadian(w));
	y = sin(Math::DegreeToRadian(w));

	return *this;
}

Vector2 Vector2::RotatedBy(float w)
{
	return Vector2();
}

Vector2 Vector2::Normalized(void) const
{
	float d = Length();

	if (d <= Math::EPSILON && -d <= Math::EPSILON)
		return Vector2(x, y);

	return Vector2(x / d, y / d);
}

Vector2& Vector2::Normalize(void)
{
	float d = Length();

	if (d <= Math::EPSILON && -d <= Math::EPSILON)
		return *this;

	x /= d;
	y /= d;
	return *this;
}

#include "Vector3.h"

Vector3 Vector2::GetVector3()
{
	return Vector3(x, y, 0);
}

std::ostream& operator<< (std::ostream& os, Vector2& rhs)
{
	os << rhs.x << ", " << rhs.y;
	return os;
}

Vector2 operator*(float scalar, const Vector2& rhs)
{
	return rhs * scalar;
}

float Vector2::Dist(const Vector2& rhs) const
{
	return sqrt(((x - rhs.x)*(x - rhs.x)) + ((y - rhs.y)*(y - rhs.y)));
}

float Vector2::DistSquared(const Vector2& rhs) const
{
	return ((x - rhs.x)*(x - rhs.x)) + ((y - rhs.y)*(y - rhs.y));
}