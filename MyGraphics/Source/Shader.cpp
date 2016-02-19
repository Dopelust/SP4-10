#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <stdlib.h>
#include <string.h>

#include "Shader.h"
#include "GraphicsEngine.h"

Shader* Shader::shader = NULL;

Shader::Shader() : informV(false), informP(false), informOrtho(false), informed(false)
{
}
Shader::~Shader()
{
	glDeleteProgram(programID);
}

void Shader::Load(const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	programID = ProgramID;
}

GLuint Shader::GetProgramID()
{
	return programID;
}

void Shader::InformOrtho(bool ortho)
{
	informOrtho = ortho;
}

void Shader::InformV(bool v)
{
	informV = v;
}

void Shader::InformP(bool p)
{
	informP = p;
}

void Shader::Flush()
{
	informed = false;
}

void Shader::GetUniformLocation(const char* uniform)
{
	if (m_parameters.find(uniform) == m_parameters.end())
	{
		m_parameters[uniform] = glGetUniformLocation(programID, (char*)uniform);
	}
}

void Shader::SetUniform1fv(const char * uniform, const GLfloat * i, unsigned arraySize)
{
	GetUniformLocation(uniform);
	glUniform1fv(m_parameters[uniform], arraySize, i);
}

void Shader::SetUniform2fv(const char * uniform, const GLfloat * i, unsigned arraySize)
{
	GetUniformLocation(uniform);
	glUniform2fv(m_parameters[uniform], arraySize, i);
}

void Shader::SetUniform3fv(const char * uniform, const GLfloat * i, unsigned arraySize)
{
	GetUniformLocation(uniform);
	glUniform3fv(m_parameters[uniform], arraySize, i);
}

void Shader::SetUniform4fv(const char * uniform, const GLfloat * i, unsigned arraySize)
{
	GetUniformLocation(uniform);
	glUniform4fv(m_parameters[uniform], arraySize, i);
}

void Shader::SetUniformMatrix4fv(const char* uniform, const GLfloat* i)
{
	GetUniformLocation(uniform);
	glUniformMatrix4fv(m_parameters[uniform], 1, GL_FALSE, i);
}

void Shader::Use()
{
	if (shader != this)
	{
		glUseProgram(programID);
		shader = this;

		if (!informed)
		{
			if (informV)
				Graphics.UpdateV(this);

			if (informP)
				Graphics.UpdateP(this);

			else if (informOrtho)
				Graphics.UpdateP(this, true);

			informed = true;
		}
	}
}

void Shader::SetUniform1i(const char * uniform, int i)
{
	GetUniformLocation(uniform);
	glUniform1i(m_parameters[uniform], i);
}
void Shader::SetUniform2i(const char * uniform, int i, int j)
{
	GetUniformLocation(uniform);
	glUniform2i(m_parameters[uniform], i, j);
}
void Shader::SetUniform3i(const char * uniform, int i, int j, int k)
{
	GetUniformLocation(uniform);
	glUniform3i(m_parameters[uniform], i, j, k);
}
void Shader::SetUniform4i(const char * uniform, int i, int j, int k, int l)
{
	GetUniformLocation(uniform);
	glUniform4i(m_parameters[uniform], i, j, k, l);
}

void Shader::SetUniform1f(const char * uniform, float i)
{
	GetUniformLocation(uniform);
	glUniform1f(m_parameters[uniform], i);
}
void Shader::SetUniform2f(const char * uniform, float i, float j)
{
	GetUniformLocation(uniform);
	glUniform2f(m_parameters[uniform], i, j);
}
void Shader::SetUniform3f(const char * uniform, float i, float j, float k)
{
	GetUniformLocation(uniform);
	glUniform3f(m_parameters[uniform], i, j, k);
}
void Shader::SetUniform4f(const char * uniform, float i, float j, float k, float l)
{
	GetUniformLocation(uniform);
	glUniform4f(m_parameters[uniform], i, j, k, l);
}
