#pragma once

class FBO;
class Texture;
class PostProcess;

class PostProcessor
{
public:
	enum PostProcesses
	{
		BLOOM,
		NUM_PROCESSES,
	};

	static PostProcessor& Instance();

	void Init(int width, int height);
	void Resize(int width, int height);
	void Exit();

	Texture* Pass(PostProcesses pp, Texture* input = 0);

	PostProcess* process[NUM_PROCESSES];
	bool& GetEnabled(PostProcesses pp);

private:
	PostProcessor();
	~PostProcessor();

	FBO* fbo;
};