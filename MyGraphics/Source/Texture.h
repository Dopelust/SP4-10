#pragma once

#include "Vector2.h"
#include "Vector4.h"

#include <GL/glew.h>
#include <iostream>

using namespace::std;

class Texture
{
public:
	Texture();

	Texture(int width, int height,
		GLint internalFormat = GL_RGBA8,
		GLint format = GL_RGBA,
		GLenum type = GL_UNSIGNED_BYTE,
		const GLvoid* pixels = NULL,
		GLint magFilter = GL_NEAREST,
		GLint minFilter = GL_NEAREST,
		GLint wrap = GL_CLAMP_TO_EDGE);

	Texture(const char* filepath,
		GLint magFilter = GL_NEAREST,
		GLint minFilter = GL_NEAREST,
		GLint wrap = GL_CLAMP_TO_EDGE);

	~Texture();

	GLuint GetID();
	void Bind(unsigned i = 0);

	void GenerateMipmap();
	void MaxAnisotropy();

	void Resize(int width, int height,
		GLint internalFormat = GL_RGBA8,
		GLint format = GL_RGBA,
		GLenum type = GL_UNSIGNED_BYTE,
		const GLvoid* pixels = NULL);

	static void Unbind();
	static Vector2 GetOffset(int index, int rows);
	static Vector4 GetUV(int index, int rows);

private:
	GLuint id;
};