#ifndef SHADER_H
#define SHADER_H

#include "Vector3.h"

#include <map>
using namespace::std;

#include <GL/glew.h>

class ShaderManager;
class Shader
{
public:
	GLuint GetProgramID();
	
	void InformOrtho(bool ortho = true);
	void InformV(bool v = true);
	void InformP(bool p = true);

	void Flush();

	void Use();
	void SetUniform1i(const char* uniform, int i);
	void SetUniform2i(const char* uniform, int i, int j);
	void SetUniform3i(const char* uniform, int i, int j, int k);
	void SetUniform4i(const char* uniform, int i, int j, int k, int l);
	void SetUniform1f(const char* uniform, float i);
	void SetUniform2f(const char* uniform, float i, float j);
	void SetUniform3f(const char* uniform, float i, float j, float k);
	void SetUniform4f(const char* uniform, float i, float j, float k, float l);
	void SetUniform1fv(const char* uniform, const GLfloat* i, unsigned arraySize = 1);
	void SetUniform2fv(const char* uniform, const GLfloat* i, unsigned arraySize = 1);
	void SetUniform3fv(const char* uniform, const GLfloat* i, unsigned arraySize = 1);
	void SetUniform4fv(const char* uniform, const GLfloat* i, unsigned arraySize = 1);
	void SetUniformMatrix4fv(const char* uniform, const GLfloat* i);
private:
	friend ShaderManager;

	Shader();
	~Shader();

	static Shader* shader;

	void Load(const char * vertex_file_path, const char * fragment_file_path);
	void GetUniformLocation(const char* uniform);

	GLuint programID;
	map<string, unsigned> m_parameters;

	bool informV;
	bool informP;
	bool informOrtho;

	bool informed;
};


#endif
