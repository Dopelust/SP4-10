#include "PostProcess.h"
#include "GraphicsEngine.h"
#include "LUAEngine.h"

#include <iostream>

PostProcess::PostProcess() : shader(NULL), fbo(NULL), attachment(0), enabled(true)
{
}

PostProcess::~PostProcess()
{
}

void PostProcess::Init()
{
}

void PostProcess::Exit()
{
}

void PostProcess::Resize(int width, int height)
{
}

void PostProcess::Assign(FBO * fbo, int attachment)
{
	this->fbo = fbo;
	this->attachment = attachment;
}