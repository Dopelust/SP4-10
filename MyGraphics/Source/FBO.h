#ifndef FBO_H
#define FBO_H

#include <GL/glew.h>

#include <vector>
using namespace::std;

class Texture;

class FBO
{
public:
	FBO();
	FBO(int width, int height);
    virtual ~FBO();

    void BindForWriting(bool clearColor = false);
	void BindForReading();

	static void Unbind();

	void SetDrawBuffer(int attachment, bool clear = true);
	void SetDrawBuffers(int count);

	void Attach(Texture* texture, GLenum attachment);

	int GetWidth();
	int GetHeight();

	Texture* GetActiveTexture();
	Texture* GetTexture(unsigned i = 0);
	void BindTextures();
	
	void Resize(int width, int height);
	static void Render();

protected:
	GLuint fbo;
	int currentDrawBuffer;
	int width, height;

	vector<Texture*> texture;

	static FBO* activeFBO;
};

#endif
