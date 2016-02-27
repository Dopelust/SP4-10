#include <iostream>
#include "GBuffer.h"
#include "PostProcessor.h"
#include "GraphicsEngine.h"
#include "Texture.h"
#include "FBO.h"
#include "Mesh2D.h"
#include "Assets.h"

#include "Scene/Camera.h"
#define camera Camera::current

#include "Screen.h"

GraphicsEngine& GraphicsEngine::Instance()
{
	static GraphicsEngine graphics;
	return graphics;
}

void GraphicsEngine::Start()
{
	view.SetToLookAt(camera->position.x, camera->position.y, camera->position.z, camera->position.x + camera->direction.x, camera->position.y + camera->direction.y, camera->position.z + camera->direction.z, camera->up.x, camera->up.y, camera->up.z);
	projection.SetToPerspective(camera->fov, Screen.GetAspectRatio(), 0.05, 3000);	
}


void GraphicsEngine::ForwardPass(bool pass)
{
	switch (pass)
	{
	case 0:
	{
		gBuffer->StartForwardPass();
		GetShader("Forward")->Use();

		break;
	}
	case 1:
	{
		glDisable(GL_DEPTH_TEST);

		break;
	}
	}
}

#include "GameEngine.h"

void GraphicsEngine::Finish()
{
	Texture* output = gBuffer->GetOutput();

	output = pp->Pass(PostProcessor::BLOOM, output);

	FinalPass(output);
	Resource.shader.Flush();
}

Texture* GraphicsEngine::BlurCurrentOutput(float radius, bool halfRes)
{
	Texture* texture = GaussianBlur(gBuffer->GetOutput(), radius, halfRes);
	texture->Bind();

	return texture;
}

void GraphicsEngine::FinalPass(Texture * texture)
{
	FBO::Unbind();
	GetShader("FBO")->Use();
	GetShader("FBO")->SetUniform1f("overlay", Engine.GetTransition() - 0.02);

	texture->Bind();
	FBO::Render();
}

void GraphicsEngine::InitFBO()
{
	gBuffer->Init(Screen.width, Screen.height);

	//Blur
	frameBuffer[BLUR] = new FBO(Screen.width, Screen.height);
	//Color
	frameBuffer[BLUR]->Attach(new Texture(frameBuffer[BLUR]->GetWidth(), frameBuffer[BLUR]->GetHeight()),
		GL_COLOR_ATTACHMENT0);
	//Color2
	frameBuffer[BLUR]->Attach(new Texture(frameBuffer[BLUR]->GetWidth(), frameBuffer[BLUR]->GetHeight()),
		GL_COLOR_ATTACHMENT1);
	frameBuffer[BLUR]->Attach(new Texture(frameBuffer[BLUR]->GetWidth(), frameBuffer[BLUR]->GetHeight()),
		GL_COLOR_ATTACHMENT2);

	//Half
	frameBuffer[HALF] = new FBO(Screen.width * 0.5f, Screen.height * 0.5f);
	//Color
	frameBuffer[HALF]->Attach(new Texture(frameBuffer[HALF]->GetWidth(), frameBuffer[HALF]->GetHeight()),
		GL_COLOR_ATTACHMENT0);
	//Color2
	frameBuffer[HALF]->Attach(new Texture(frameBuffer[HALF]->GetWidth(), frameBuffer[HALF]->GetHeight()),
		GL_COLOR_ATTACHMENT1);
	frameBuffer[HALF]->Attach(new Texture(frameBuffer[HALF]->GetWidth(), frameBuffer[HALF]->GetHeight()),
		GL_COLOR_ATTACHMENT2);
}

void GraphicsEngine::Init(int width, int height)
{
	InitFBO();
	Resource.Init();
	Quad.Init();
	font->Init();
	pp->Init(width, height);

	glLineWidth(2);
	glEnable(GL_CULL_FACE);
}

void GraphicsEngine::Exit()
{
	pp->Exit();
}

Shader * GraphicsEngine::GetShader(const char * key)
{
	return Resource.GetShader(key);
}

void GraphicsEngine::UpdateV(Shader * shader, bool identity)
{
	if (identity)
		shader->SetUniformMatrix4fv("V", &Mtx44::GetIdentity().a[0]);
	else
		shader->SetUniformMatrix4fv("V", &view.a[0]);
}

void GraphicsEngine::UpdateP(Shader * shader, bool ortho)
{
	if (ortho)
		shader->SetUniformMatrix4fv("P", &screen_projection.a[0]);
	else
		shader->SetUniformMatrix4fv("P", &projection.a[0]);
}

void GraphicsEngine::Render2D(const char * shader, int x, int y, bool identity)
{
	screen_projection.SetToOrtho(0, x, 0, y, -10, 10);
	Quad.RenderInstances(shader, identity);

	RenderText();
}

void GraphicsEngine::RenderText()
{
	font->Render();
}

void GraphicsEngine::RenderOnScreen(Texture * texture)
{
	GetShader("FBO")->Use();
	texture->Bind();
	FBO::Render();
}

FBO * GraphicsEngine::GetFBO(fboType f)
{
	return frameBuffer[f];
}

GraphicsEngine::GraphicsEngine() : 
	font(&FontManager::Instance()), 
	gBuffer(&GBuffer::Instance()), 
	pp(&PostProcessor::Instance())
{
	for (unsigned i = 0; i < NUM_FBO; ++i)
		frameBuffer[i] = NULL;
}

GraphicsEngine::~GraphicsEngine()
{
	for (unsigned i = 0; i < NUM_FBO; ++i)
		delete frameBuffer[i];
}

Texture* GraphicsEngine::GaussianBlur(Texture* input, float radius, bool halfRes)
{
	FBO* blurFBO = GetFBO(BLUR);

	if (halfRes)
		blurFBO = GetFBO(HALF);

	blurFBO->BindForWriting();
	blurFBO->SetDrawBuffer(0);

	GetShader("Gaussian")->Use();
	GetShader("Gaussian")->SetUniform2f("blurSize", 1.0f / Screen.width * (1 + halfRes), 1.0f / Screen.height * (1 + halfRes));
	GetShader("Gaussian")->SetUniform1f("radius", radius);

	//Horizontal Blur
	GetShader("Gaussian")->SetUniform1i("verticalBlur", false);
	input->Bind();
	FBO::Render();

	blurFBO->SetDrawBuffer(1);

	//Vertical Blur
	GetShader("Gaussian")->SetUniform1i("verticalBlur", true);
	blurFBO->GetTexture()->Bind();
	FBO::Render();

	return blurFBO->GetActiveTexture();
}

Texture * GraphicsEngine::Combine(Texture * input1, Texture * input2)
{
	GetFBO(BLUR)->BindForWriting();
	GetFBO(BLUR)->SetDrawBuffer(2);

	GetShader("Combine")->Use();

	input1->Bind();
	input2->Bind(1);

	FBO::Render();

	return GetFBO(BLUR)->GetActiveTexture();
}

void GraphicsEngine::Resize(int width, int height)
{
	gBuffer->Resize(width, height);

	if (frameBuffer[BLUR])
		frameBuffer[BLUR]->Resize(width, height);
	if (frameBuffer[HALF])
		frameBuffer[HALF]->Resize(width * 0.5f, height * 0.5f);

	pp->Resize(width, height);
}

const Mtx44 & GraphicsEngine::GetView()
{
	return view;
}

const Mtx44 & GraphicsEngine::GetProjection()
{
	return projection;
}

const Mtx44 & GraphicsEngine::GetProjection2D()
{
	return screen_projection;
}
