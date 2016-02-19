#include "GBuffer.h"
#include "FBO.h"
#include "Texture.h"

GBuffer& GBuffer::Instance()
{
	static GBuffer gBuffer;
	return gBuffer;
}

void GBuffer::Init(int width, int height)
{
	fbo = new FBO(width, height);

	//Position
	fbo->Attach(new Texture(fbo->GetWidth(), fbo->GetHeight(), GL_RGBA16F, GL_RGBA, GL_FLOAT), GL_COLOR_ATTACHMENT0);
	//Normal
	fbo->Attach(new Texture(fbo->GetWidth(), fbo->GetHeight(), GL_RGBA16F, GL_RGBA, GL_FLOAT), GL_COLOR_ATTACHMENT1);
	//Difuse
	fbo->Attach(new Texture(fbo->GetWidth(), fbo->GetHeight()), GL_COLOR_ATTACHMENT2);
	//Specular
	fbo->Attach(new Texture(fbo->GetWidth(), fbo->GetHeight(), GL_RGBA16F, GL_RGBA, GL_FLOAT), GL_COLOR_ATTACHMENT3);

	//Forward
	fbo->Attach(new Texture(fbo->GetWidth(), fbo->GetHeight()), GL_COLOR_ATTACHMENT4);

	//Depth
	fbo->Attach(new Texture(fbo->GetWidth(), fbo->GetHeight(), GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE),
		GL_DEPTH_ATTACHMENT);

	fbo->SetDrawBuffers(4);
}

void GBuffer::Resize(int width, int height)
{
	if (fbo)
	{
		fbo->Resize(width, height);
		fbo->GetTexture(POSITION_MAP)->Resize(width, height, GL_RGBA16F, GL_RGBA, GL_FLOAT);
		fbo->GetTexture(NORMAL_MAP)->Resize(width, height, GL_RGBA16F, GL_RGBA, GL_FLOAT);
		fbo->GetTexture(SPECULAR_MAP)->Resize(width, height, GL_RGBA16F, GL_RGBA, GL_FLOAT);
		fbo->GetTexture(DEPTH_TEXTURE)->Resize(width, height, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE);
	}
}

void GBuffer::BindForWriting(bool clearColor)
{
	fbo->BindForWriting(clearColor);
}

void GBuffer::Bind(attachmentType attachment, int textureUnit)
{
	fbo->GetTexture(attachment)->Bind(textureUnit);
}

Texture * GBuffer::GetOutput()
{
	return fbo->GetTexture(FORWARD_TEXTURE);
}

void GBuffer::StartGPass()
{
	fbo->BindForWriting();
	fbo->SetDrawBuffers(4);
	glClear(GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void GBuffer::StartDirLightPass()
{
	fbo->BindForWriting();
	fbo->SetDrawBuffer(FORWARD_TEXTURE);

	for (int i = 0; i < 4; ++i)
		fbo->GetTexture(i)->Bind(i);
}

void GBuffer::StartForwardPass()
{
	fbo->BindForWriting();
	fbo->SetDrawBuffer(FORWARD_TEXTURE, false);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

GBuffer::GBuffer() : fbo(NULL)
{
}

GBuffer::~GBuffer()
{
	if (fbo)
		delete fbo;
}
