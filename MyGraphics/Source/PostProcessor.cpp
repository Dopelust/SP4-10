#include "PostProcessor.h"
#include "Bloom.h"
#include "FBO.h"
#include "Texture.h"

#include <iostream>

PostProcessor& PostProcessor::Instance()
{
	static PostProcessor pp;
	return pp;
}

void PostProcessor::Init(int width, int height)
{
	Bloom* bloom = new Bloom();
	bloom->Init();

	process[BLOOM] = bloom;

	fbo = new FBO(width, height);

	fbo->Attach(new Texture(fbo->GetWidth(), fbo->GetHeight()), GL_COLOR_ATTACHMENT0);
	bloom->Assign(fbo, 0);
}

void PostProcessor::Resize(int width, int height)
{
	if (fbo)
	{
		fbo->Resize(width, height);

		for (auto& p : process)
			p->Resize(width, height);
	}
}

void PostProcessor::Exit()
{
	for (auto& p : process)
		p->Exit();
}

Texture * PostProcessor::Pass(PostProcesses pp, Texture * input)
{
	return process[pp]->Pass(input);
}

bool & PostProcessor::GetEnabled(PostProcesses pp)
{
	return process[pp]->enabled;
}

PostProcessor::PostProcessor() : fbo(NULL)
{
}

PostProcessor::~PostProcessor()
{
	for (auto& p : process)
		delete p;
}
