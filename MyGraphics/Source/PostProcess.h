#pragma once

class LUAEngine;
class Texture;
class Shader;
class FBO;
class GraphicsEngine;
class PostProcessor;

class PostProcess
{
public:
	PostProcess();
	virtual ~PostProcess();

	virtual void Init();
	virtual void Exit();

	virtual Texture* Pass(Texture* input) = 0;

	virtual void Resize(int width, int height);
	virtual void Assign(FBO* fbo, int attachment);

	bool enabled;

protected:
	Shader* shader;

	FBO* fbo;
	int attachment;
};