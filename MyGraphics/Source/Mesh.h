#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include "GL\glew.h"
#include "Instance.h"

using namespace::std;

class Vertex;
class Mesh
{
public:
	Mesh(vector<Vertex>& vertex_buffer_data, vector<GLuint>& index_buffer_data);
	virtual ~Mesh();
	GLenum mode;

	void Render();
	void Render(const DrawInstance& instance);

private:
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

	friend DrawInstance;
};

#endif