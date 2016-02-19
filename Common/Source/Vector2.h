#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

struct Vector3;
struct Vector2
{
	float x;
	float y;

	Vector2(float a = 0, float b = 0);
	Vector2(const Vector2 &rhs);

	~Vector2();

	void Set(const float& a = 0, const float& b = 0); //Set all data
	void SetZero(void); //Set all data to zero
	bool IsZero(void) const; //Check if data is zero

	Vector2 operator+(const Vector2& rhs) const; //Vector addition
	Vector2& operator+=(const Vector2& rhs);

	Vector2 operator-(const Vector2& rhs) const; //Vector subtraction
	Vector2& operator-=(const Vector2& rhs);

	Vector2 operator-(void) const; //Unary negation

	Vector2 operator*(const Vector2& rhs) const; //Vector multiplication
	Vector2 operator*(float scalar) const; //Scalar multiplication
	Vector2& operator*=(float scalar);

	Vector2 operator/(float scalar) const; //Scalar division
	Vector2& operator/=(float scalar);

	bool operator==(const Vector2& rhs) const; //Equality check
	bool operator!= (const Vector2& rhs) const; //Inequality check

	Vector2& operator=(const Vector2& rhs); //Assignment operator

	float Length(void) const; //Get magnitude
	float LengthSquared(void) const; //Get square of magnitude

	float Dist(const Vector2& rhs) const; //Dist between 2 vectors
	float DistSquared(const Vector2& rhs) const; //Dist between 2 vectors

	float Dot(const Vector2& rhs) const; //Dot product
	Vector2 Cross() const; //Cross product

	Vector2& Rotate(float w);
	Vector2 RotatedBy(float w);

	Vector2 Normalized(void) const;
	Vector2& Normalize(void);

	friend std::ostream& operator<<(std::ostream& os, Vector2& rhs); //print to ostream

	friend Vector2 operator*(float scalar, const Vector2& rhs); //what is this for?	

	Vector3 GetVector3();
};

#endif
