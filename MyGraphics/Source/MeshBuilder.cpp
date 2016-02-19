#include "vertex.h"
#include "MeshBuilder.h"
#include "MyMath.h"
#include <iomanip>
#include <GL\glew.h>
#include <vector>

#define PI 3.14159265

using std::cout;
using std::endl;

Mesh* MeshBuilder::GenerateLine(Vector3 color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(0, 0, -0.5 * length);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0, 0.5 * length);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);

	Mesh *mesh = new Mesh(vertex_buffer_data, index_buffer_data);
	mesh->mode = GL_LINES;

	return mesh;
}

Mesh* MeshBuilder::GenerateRay(Vector3 color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(0, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0, length);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);

	Mesh *mesh = new Mesh(vertex_buffer_data, index_buffer_data);
	mesh->mode = GL_LINES;

	return mesh;
}

Mesh* MeshBuilder::GenerateHorizontalQuad(Vector3 color, float lengthX, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-0.5f * lengthX, 0.0f, 0.5f * lengthZ);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, 0.0f, 0.5f * lengthZ);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, 0.0f, -0.5f * lengthZ);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, 0.0f, -0.5f * lengthZ);
	v.normal.Set(0, 1, 0);
	v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);


	std::vector<GLuint> index_buffer_data;

	unsigned int index[6] = {
		0,1,2,2,1,3
	};

	for (int i = 0; i < 6; i++)
	{
		index_buffer_data.push_back(index[i]);
	}

	Mesh *mesh = new Mesh(vertex_buffer_data, index_buffer_data);
	mesh->mode = GL_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateVerticalQuad(Vector3 color, float lengthX, float lengthY)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.0f);
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.0f);
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1, 0);

	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.0f);
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.0f);
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;

	unsigned int index[6] = {
		3,0,2,1,2,0
	};

	for (int i = 0; i < 6; i++)
	{
		index_buffer_data.push_back(index[i]);
	}

	Mesh *mesh = new Mesh(vertex_buffer_data, index_buffer_data);
	mesh->mode = GL_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCube(Vector3 color, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	//TOP
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); v.normal.Set(0, 1, 0); v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); v.normal.Set(0, 1, 0); v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); v.normal.Set(0, 1, 0); v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); v.normal.Set(0, 1, 0); v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);

	//BOTTOM
	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); v.normal.Set(0, -1, 0); v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); v.normal.Set(0, -1, 0); v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); v.normal.Set(0, -1, 0); v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); v.normal.Set(0, -1, 0); v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);

	//RIGHT
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); v.normal.Set(1, 0, 0); v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); v.normal.Set(1, 0, 0); v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); v.normal.Set(1, 0, 0); v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); v.normal.Set(1, 0, 0); v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);

	//LEFT
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); v.normal.Set(-1, 0, 0); v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); v.normal.Set(-1, 0, 0); v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); v.normal.Set(-1, 0, 0); v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); v.normal.Set(-1, 0, 0); v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);

	//FRONT
	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); v.normal.Set(0, 0, 1); v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); v.normal.Set(0, 0, 1); v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); v.normal.Set(0, 0, 1); v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); v.normal.Set(0, 0, 1); v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);

	//BACK
	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); v.normal.Set(0, 0, -1); v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); v.normal.Set(0, 0, -1); v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); v.normal.Set(0, 0, -1); v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); v.normal.Set(0, 0, -1); v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;

	for (int i = 0; i < 6; i++)
	{
		index_buffer_data.push_back(0 + (i * 4));
		index_buffer_data.push_back(1 + (i * 4));
		index_buffer_data.push_back(2 + (i * 4));
		index_buffer_data.push_back(2 + (i * 4));
		index_buffer_data.push_back(1 + (i * 4));
		index_buffer_data.push_back(3 + (i * 4));
	}

	Mesh *mesh = new Mesh(vertex_buffer_data, index_buffer_data);
	mesh->mode = GL_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCubeOutline(Vector3 color, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	for (float i = -0.5f; i < 0.6f; ++i)
	{
		v.pos.Set(-lengthX * 0.5f, i * lengthY, lengthZ * 0.5f); 
		vertex_buffer_data.push_back(v);
		v.pos.Set(lengthX * 0.5f, i * lengthY, lengthZ * 0.5f); 
		vertex_buffer_data.push_back(v);

		v.pos.Set(-lengthX * 0.5f, i * lengthY, -lengthZ * 0.5f);
		vertex_buffer_data.push_back(v);
		v.pos.Set(lengthX * 0.5f, i * lengthY, -lengthZ * 0.5f); 
		vertex_buffer_data.push_back(v);
	}

	std::vector<GLuint> index_buffer_data;

	int offset = 0;
	for (unsigned i = 0; i < 2; ++i)
	{
		index_buffer_data.push_back(0 + offset);
		index_buffer_data.push_back(1 + offset);
		index_buffer_data.push_back(2 + offset);
		index_buffer_data.push_back(3 + offset);
		index_buffer_data.push_back(0 + offset);
		index_buffer_data.push_back(2 + offset);
		index_buffer_data.push_back(1 + offset);
		index_buffer_data.push_back(3 + offset);

		offset += 4;
	}

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(7);

	Mesh *mesh = new Mesh(vertex_buffer_data, index_buffer_data);
	mesh->mode = GL_LINES;

	return mesh;
}

float sphereX(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
}

float sphereY(float phi)
{
	return sin(Math::DegreeToRadian(phi));
}

float sphereZ(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateSphere(Vector3 color, unsigned numStack, unsigned numSlice, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	float degreePerStack = 180.0f / numStack;
	float degreePerSlice = 360.0f / numSlice;

	for (unsigned stack = 0; stack <= numStack; stack++)
	{
		float phi = -90 + stack * degreePerStack;

		for (unsigned slice = 0; slice <= numSlice; slice++)
		{
			float theta = slice * degreePerSlice;
			v.pos.Set(radius * sphereX(phi, theta), radius * sphereY(phi), radius * sphereZ(phi, theta));
			v.normal.Set(sphereX(phi, theta), sphereY(phi), sphereZ(phi, theta));
			vertex_buffer_data.push_back(v);

		}
	}

	std::vector<GLuint> index_buffer_data;

	for (unsigned stack = 0; stack < numStack; stack++)
	{
		for (unsigned slice = 0; slice < numSlice; slice++)
		{
			index_buffer_data.push_back(stack * (numSlice + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlice + 1) + slice);
		}
	}

	Mesh *mesh = new Mesh(vertex_buffer_data, index_buffer_data);
	mesh->mode = GL_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &file_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Vector3> vertices;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);

	Mesh *mesh = new Mesh(vertex_buffer_data, index_buffer_data);
	mesh->mode = GL_TRIANGLES;

	return mesh;
}