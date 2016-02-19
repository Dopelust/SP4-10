#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "vertex.h"
#include "LoadOBJ.h"

class MeshBuilder
{
public:
	static Mesh* GenerateLine(Vector3 color, float length);
	static Mesh* GenerateRay(Vector3 color, float length);

	static Mesh* GenerateHorizontalQuad(Vector3 color, float lengthX, float lengthZ);
	static Mesh* GenerateVerticalQuad(Vector3 color, float lengthX, float lengthY);

	static Mesh* GenerateCube(Vector3 color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateCubeOutline(Vector3 color, float lengthX, float lengthY, float lengthZ);
	
	static Mesh* GenerateSphere(Vector3 color, unsigned numStack, unsigned numSlice, float radius);

	static Mesh* GenerateOBJ(const std::string &file_path);
};

#endif