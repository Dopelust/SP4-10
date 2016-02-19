#include "Camera.h"

Camera* Camera::current = NULL;

Camera::Camera() : position(0,0,0), orientation(180,0), fov(70)
{
	Update();
}

Camera::~Camera()
{
}

void Camera::Update()
{
	direction.SphericalToCartesian(orientation.x, orientation.y);
	right.SphericalToCartesian(orientation.x - 90, 0);
	up.Set(0, 1, 0);
}

Vector3 Camera::GetDirectionInverse()
{
	return Vector3(1.0f / direction.x, 1.0f / direction.y, 1.0f / direction.z);
}