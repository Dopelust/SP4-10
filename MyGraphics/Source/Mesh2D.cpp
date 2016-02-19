#include "Mesh2D.h"
#include "Shader.h"
#include "Texture.h"
#include "Assets.h"

void Mesh2D::Init()
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(0,0,0);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(1,0,0);
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);
	
	v.pos.Set(1,1,0);
	v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0,1,0);
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

	indexSize = 6;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3)));

	glGenBuffers(1, &buffer[INDEX_BUFFER]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()  * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	glGenBuffers(1, &buffer[MODEL_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[MODEL_BUFFER]);

	for (unsigned int i = 0; i < 4; i++)
	{
		glEnableVertexAttribArray(2 + i);
		glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(Mtx44), (const GLvoid*)(sizeof(GLfloat) * i * 4));
		glVertexAttribDivisor(2 + i, 1);
	}

	glGenBuffers(1, &buffer[COLOR_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[COLOR_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4), &Vector4(1, 1, 1), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), (void*)0);
	glVertexAttribDivisor(6, 1);

	glGenBuffers(1, &buffer[TEXTURE_OFFSET_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[TEXTURE_OFFSET_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4), &Vector4(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), (void*)0);
	glVertexAttribDivisor(7, 1);

	glBindVertexArray(0);
}

#include "GraphicsEngine.h"

void Mesh2D::RenderInstances(const char* shader, bool identity)
{
	Resource.GetShader(shader)->Use();
	Graphics.UpdateP(Resource.GetShader(shader), true);
	Graphics.UpdateV(Resource.GetShader(shader), identity);

	for (auto& layer : layerMap)
	{
		if (layer.second.instances.empty())
			continue;

		for (auto& i : layer.second.instances)
		{
			if (layer.second.instanceMap[i].NumInstance())
			{
				if (i)
				{
					i->Bind();
					Resource.GetShader(shader)->SetUniform1i("textureEnabled", true);
				}
				else
					Resource.GetShader(shader)->SetUniform1i("textureEnabled", false);

				layer.second.instanceMap[i].Bind(this);

				glBindVertexArray(VAO);
				glDrawElementsInstanced(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0, layer.second.instanceMap[i].NumInstance());
				glBindVertexArray(0);
			}
		}

		layer.second.instances.clear();
		layer.second.instanceMap.clear();
	}
}

void Mesh2D::Render(const DrawInstance2D & instance)
{
	instance.Bind(this);

	glBindVertexArray(VAO);
	glDrawElementsInstanced(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0, instance.NumInstance());
	glBindVertexArray(0);
}

Mesh2D& Mesh2D::Instance()
{
	static Mesh2D mesh2D;
	return mesh2D;
}

DrawInstance2D & Mesh2D::GetInstance(Texture * texture, int layer)
{
	if (layerMap[layer].instanceMap.find(texture) == layerMap[layer].instanceMap.end())
		layerMap[layer].instances.push_back(texture);
	
	return layerMap[layer].instanceMap[texture];
}

Mesh2D::Mesh2D() : indexSize(0)
{
}

Mesh2D::~Mesh2D()
{
	if (indexSize)
	{
		glDeleteVertexArrays(1, &VAO);

		for (unsigned i = 0; i < NUM_BUFFERS; ++i)
			glDeleteBuffers(1, &buffer[i]);
	}
}
