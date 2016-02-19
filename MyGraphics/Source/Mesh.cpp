#include "Mesh.h"
#include "Texture.h"
#include "vertex.h"

Vertex& GetVertex(vector<Vertex>& vertex_buffer_data, int index)
{
	if (vertex_buffer_data.size() > index)
		return vertex_buffer_data[index];

	return Vertex();
}

Mesh::Mesh(vector<Vertex>& vertex_buffer_data, vector<GLuint>& index_buffer_data) : mode(GL_TRIANGLES)
{
	for (int i = 0; i < (int)index_buffer_data.size() - 3; i += 3)
	{
		Vertex& v0 = GetVertex(vertex_buffer_data, index_buffer_data[i]);
		Vertex& v1 = GetVertex(vertex_buffer_data, index_buffer_data[i + 1]);
		Vertex& v2 = GetVertex(vertex_buffer_data, index_buffer_data[i + 2]);

		Vector3 Edge1 = Vector3(v1.pos.x, v1.pos.y, v1.pos.z) - Vector3(v0.pos.x, v0.pos.y, v0.pos.z);
		Vector3 Edge2 = Vector3(v2.pos.x, v2.pos.y, v2.pos.z) - Vector3(v0.pos.x, v0.pos.y, v0.pos.z);

		float DeltaU1 = v1.texCoord.x - v0.texCoord.x;
		float DeltaV1 = v1.texCoord.y - v0.texCoord.y;
		float DeltaU2 = v2.texCoord.x - v0.texCoord.x;
		float DeltaV2 = v2.texCoord.y - v0.texCoord.y;

		float f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

		Vector3 Tangent, Bitangent;

		Tangent.x = f * (DeltaV2 * Edge1.x - DeltaV1 * Edge2.x);
		Tangent.y = f * (DeltaV2 * Edge1.y - DeltaV1 * Edge2.y);
		Tangent.z = f * (DeltaV2 * Edge1.z - DeltaV1 * Edge2.z);

		Bitangent.x = f * (-DeltaU2 * Edge1.x - DeltaU1 * Edge2.x);
		Bitangent.y = f * (-DeltaU2 * Edge1.y - DeltaU1 * Edge2.y);
		Bitangent.z = f * (-DeltaU2 * Edge1.z - DeltaU1 * Edge2.z);

		v0.tangent += Tangent;
		v1.tangent += Tangent;
		v2.tangent += Tangent;
	}

	for (unsigned int i = 0; i < vertex_buffer_data.size(); i++) {
		const Vector3 n = vertex_buffer_data[i].normal;
		const Vector3 t = vertex_buffer_data[i].tangent;

		vertex_buffer_data[i].tangent = (t - n * n.Dot(t)).Normalize();
	}

	/*for (unsigned int i = 0; i < vertex_buffer_data.size(); i++) {
		vertex_buffer_data[i].tangent.Normalize();
		}*/

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector3)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3)));

	glGenBuffers(1, &buffer[INDEX_BUFFER]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()  * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	glGenBuffers(1, &buffer[MODEL_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[MODEL_BUFFER]);

	for (unsigned int i = 0; i < 4; i++) 
	{
		glEnableVertexAttribArray(4 + i);
		glVertexAttribPointer(4 + i, 4, GL_FLOAT, GL_FALSE, sizeof(Mtx44), (const GLvoid*)(sizeof(GLfloat) * i * 4));
		glVertexAttribDivisor(4 + i, 1);
	}

	glGenBuffers(1, &buffer[COLOR_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[COLOR_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4), &Vector4(1, 1, 1), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), (void*)0);
	glVertexAttribDivisor(8, 1);

	glGenBuffers(1, &buffer[TEXTURE_OFFSET_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[TEXTURE_OFFSET_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2), &Vector2(0,0), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(9);
	glVertexAttribPointer(9, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)0);
	glVertexAttribDivisor(9, 1);

	glBindVertexArray(0);

	indexSize = index_buffer_data.size();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);

	for (unsigned i = 0; i < NUM_BUFFERS; ++i)
		glDeleteBuffers(1, &buffer[i]);
}	

void Mesh::Render()
{
	static DrawInstance instance(Mtx44::GetIdentity());
	Render(instance);
}

void Mesh::Render(const DrawInstance & instance)
{
	instance.Bind(this);

	glBindVertexArray(VAO);
	glDrawElementsInstanced(mode, indexSize, GL_UNSIGNED_INT, 0, instance.NumInstance());
	glBindVertexArray(0);
}

