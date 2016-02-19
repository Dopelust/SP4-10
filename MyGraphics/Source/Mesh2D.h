#pragma once

#include <vector>
#include <string>
#include <map>

#include "vertex.h"
#include "GL\glew.h"
#include "DrawInstance2D.h"

using namespace::std;

#define Quad Mesh2D::Instance()

class Texture;
class Mesh2D
{
public:
	void Init();

	void Render(const DrawInstance2D & instance);
	void RenderInstances(const char* shader = "2D", bool identity = true);

	static Mesh2D& Instance();

	DrawInstance2D& GetInstance(Texture* texture);

private:
	Mesh2D();
	~Mesh2D();

	enum BufferType
	{
		VERTEX_BUFFER,
		INDEX_BUFFER,
		MODEL_BUFFER,
		COLOR_BUFFER,
		TEXTURE_OFFSET_BUFFER,
		NUM_BUFFERS,
	};

	GLuint VAO;
	unsigned buffer[NUM_BUFFERS];
	unsigned indexSize;

	vector<Texture*> instances;
	map<Texture*, DrawInstance2D> instanceMap;

	friend DrawInstance2D;
};