#include "Texture.h"
#include <fstream>

Texture::Texture()
{
	glGenTextures(1, &id);
}
Texture::Texture(int width, int height, GLint internalFormat, GLint format, GLenum type, const GLvoid* pixels, GLint magFilter, GLint minFilter, GLint wrap)
{
	glGenTextures(1, &id);

	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, pixels);

	if (minFilter != GL_NEAREST && minFilter != GL_LINEAR)
		GenerateMipmap();
}

Texture::Texture(const char* filepath, GLint magFilter, GLint minFilter, GLint wrap)
{
	glGenTextures(1, &id);

	std::ifstream fileStream(filepath, ios::binary);

	if (!fileStream.is_open()) 
	{
		cout << "Failed to open " << filepath << "\n";
		return;
	}

	GLubyte		header[18];									// first 6 useful header bytes
	GLuint		bytesPerPixel;								    // number of bytes per pixel in TGA gile
	GLuint		imageSize;									    // for setting memory
	GLubyte *	data;
	GLuint		texture = 0;
	unsigned	width, height;

	fileStream.read((char*)header, 18);
	width = header[12] + header[13] * 256;
	height = header[14] + header[15] * 256;

	if (width <= 0 ||								// is width <= 0
		height <= 0 ||								// is height <=0
		(header[16] != 24 && header[16] != 32))		// is TGA 24 or 32 Bit
	{
		fileStream.close();							// close file on failure
		cout << "File header error.\n";
		return;
	}

	bytesPerPixel = header[16] / 8;						//divide by 8 to get bytes per pixel
	imageSize = width * height * bytesPerPixel;	// calculate memory required for TGA data

	data = new GLubyte[imageSize];
	fileStream.seekg(18, std::ios::beg);
	fileStream.read((char *)data, imageSize);
	fileStream.close();

	Bind();

	if (bytesPerPixel == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	else //bytesPerPixel == 4
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);

	if (minFilter != GL_NEAREST && minFilter != GL_LINEAR)
		GenerateMipmap();

	delete[]data;
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

static const double inverse[20] = { 1.0f , 1.0f / 2.0f, 1.0f / 3.0f, 1.0f / 4.0f, 1.0f / 5.0f, 1.0f / 6.0f, 1.0f / 7.0f, 1.0f / 8.0f, 1.0f / 9.0f, 1.0f / 10.0f,
1.0f / 11.f, 1.0f / 12.0f, 1.0f / 13.0f, 1.0f / 14.0f, 1.0f / 15.0f, 1.0f / 16.0f, 1.0f / 17.0f, 1.0f / 18.0f, 1.0f / 19.0f, 1.0f / 20.0f };

Vector2 Texture::GetOffset(int index, int rows)
{
	return Vector2((index % rows) * inverse[rows - 1], 1 - (((int)(index * inverse[rows - 1])) + 1) * inverse[rows - 1]);
}

Vector4 Texture::GetUV(int index, int rows)
{
 	Vector2& topLeft = GetOffset(index, rows);
	float unit = inverse[rows - 1];

	return Vector4(topLeft.x, topLeft.y, topLeft.x + unit, topLeft.y + unit);
}

void Texture::Bind(unsigned i)
{
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::GenerateMipmap()
{
	Bind();
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::MaxAnisotropy()
{
	Bind();

	float maxAnisotropy = 1;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLint)maxAnisotropy);
}

void Texture::Resize(int width, int height, GLint internalFormat, GLint format, GLenum type, const GLvoid * pixels)
{
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, pixels);
}

GLuint Texture::GetID()
{
	return id;
}