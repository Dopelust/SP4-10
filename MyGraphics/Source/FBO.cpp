#include "FBO.h"
#include "Texture.h"
#include "Screen.h"
#include <iostream>

GLenum GetAttachment(int attachment)
{
	switch (attachment)
	{
	case 0:
		return GL_COLOR_ATTACHMENT0;
	case 1:
		return GL_COLOR_ATTACHMENT1;
	case 2:
		return GL_COLOR_ATTACHMENT2;
	case 3:
		return GL_COLOR_ATTACHMENT3;
	case 4:
		return GL_COLOR_ATTACHMENT4;
	case 5:
		return GL_COLOR_ATTACHMENT5;
	}

	return GL_COLOR_ATTACHMENT0;
}

FBO* FBO::activeFBO = NULL;

FBO::FBO() : currentDrawBuffer(0)
{
	glGenFramebuffers(1, &fbo);
}

FBO::FBO(int width, int height) : currentDrawBuffer(GL_COLOR_ATTACHMENT0)
{
	glGenFramebuffers(1, &fbo);
	this->width = width;
	this->height = height;
}

FBO::~FBO()
{
	glDeleteFramebuffers(1, &fbo);

	for (auto& t : texture)
		delete t;
}

void FBO::BindForWriting(bool clearColor)
{
	if (this != activeFBO)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

		if (clearColor)
			glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, width, height);
		activeFBO = this;
	}
}

void FBO::BindForReading()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
}

void FBO::Unbind()
{
	if (activeFBO)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, Screen.width, Screen.height);

		activeFBO = NULL;
	}
}

void FBO::SetDrawBuffer(int attachment, bool clear)
{
	BindForWriting();

	glDrawBuffer(GetAttachment(attachment));

	if (clear)
		glClear(GL_COLOR_BUFFER_BIT);

	currentDrawBuffer = attachment;
}

void FBO::SetDrawBuffers(int count)
{
	BindForWriting();

	vector<GLenum> DrawBuffers;
	DrawBuffers.reserve(count);

	for (int i = 0; i < count; ++i)
		DrawBuffers.push_back(GetAttachment(i));

	glDrawBuffers(count, &DrawBuffers[0]);
	glClear(GL_COLOR_BUFFER_BIT);

	currentDrawBuffer = 0;
}

void FBO::Attach(Texture* texture, GLenum attachment)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->GetID(), 0);

	GLenum status;
	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) 
	{
		fprintf(stderr, "glCheckFramebufferStatus: error %p", status);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	this->texture.push_back(texture);
}

int FBO::GetWidth()
{
	return width;
}

int FBO::GetHeight()
{
	return height;
}

Texture * FBO::GetActiveTexture()
{
	return GetTexture(currentDrawBuffer);
}

Texture* FBO::GetTexture(unsigned i)
{
	return texture[i];
}

void FBO::BindTextures()
{
	for (int i = 0; i < texture.size(); ++i)
		texture[i]->Bind(i);
}

#include "Assets.h"
#include "Mesh.h"

void FBO::Resize(int width, int height)
{
	this->width = width;
	this->height = height;

	for (auto& t : texture)
		t->Resize(width, height);
}

void FBO::Render()
{
	Assets::Instance().GetMesh("quad")->Render();
}
