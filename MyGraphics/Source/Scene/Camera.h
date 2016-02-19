#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Vector3.h"
#include "Vector2.h"

class Scene;
class Camera
{
public:
	static Camera* current;

	Vector3 position;
	Vector3 direction, right, up;

	Vector2 orientation;
	float fov;

	void Update();
	Vector3 GetDirectionInverse();

private:
	friend Scene;

	Camera();
	~Camera();
};

#endif