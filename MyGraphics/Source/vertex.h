#ifndef VERTEX_H
#define VERTEX_H

#include "Vector2.h"
#include "Mtx44.h"

class Vertex
{
public:
	Vertex() {}

	Vector3 pos;
	Vector3 normal;
	Vector3 tangent;
	Vector2 texCoord;
};

#endif