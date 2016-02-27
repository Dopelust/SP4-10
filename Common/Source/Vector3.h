#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

struct Vector2;
struct Vector3
{
	float x; 
	float y; 
	float z;

	Vector3(float a = 0, float b = 0, float c = 0);
	Vector3(const Vector3 &rhs);
	~Vector3();
	
	void Set(float a = 0, float b = 0, float c = 0); //Set all data
	void SetZero( void ); //Set all data to zero
	bool IsZero( void ) const; //Check if data is zero

	Vector3 operator+( const Vector3& rhs ) const; //Vector addition
	Vector3& operator+=( const Vector3& rhs ); 
	
	Vector3 operator-( const Vector3& rhs ) const; //Vector subtraction
	Vector3& operator-=( const Vector3& rhs );
	
	Vector3 operator-( void ) const; //Unary negation
	
	Vector3 operator*( const Vector3& rhs ) const; //Vector multiplication
	Vector3 operator*( float scalar ) const; //Scalar multiplication
	Vector3& operator*=( float scalar );

	Vector3 operator/( float scalar ) const; //Scalar division
	Vector3& operator/=( float scalar );

	bool operator<(const Vector3& rhs) const;
	bool operator==( const Vector3& rhs ) const; //Equality check
	bool operator!= ( const Vector3& rhs ) const; //Inequality check

	Vector3& operator=(const Vector3& rhs); //Assignment operator
	
	float Length( void ) const; //Get magnitude
	float LengthSquared (void ) const; //Get square of magnitude
	
	float Dist( const Vector3& rhs ) const; //Dist between 2 vectors
	float DistSquared( const Vector3& rhs ) const; //Dist between 2 vectors

	float Dot( const Vector3& rhs ) const; //Dot product
	Vector3 Cross( const Vector3& rhs ) const; //Cross product
	
	Vector3 Normalized( void ) const;
	Vector3& Normalize( void );
	
	Vector3& Rotate(float angle, Vector3 axis);

	friend std::ostream& operator<<( std::ostream& os, const Vector3& rhs); //print to ostream

	friend Vector3 operator*( float scalar, const Vector3& rhs ); //what is this for?

	Vector3& SphericalToCartesian (float yaw, float pitch);
	Vector2 GetVector2();
};

#endif
