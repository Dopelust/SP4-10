#pragma once

#include "PostProcess.h"

class Bloom : public PostProcess
{
public:
	void Init();
	void Exit();

	Texture* Pass(Texture* input);

	void SetRadius(float radius);
	void SetIntensity(float intensity);
	void SetAmount(float amount);

protected:
	Bloom();
	~Bloom();

	friend PostProcessor;

	float intensity;
	float amount;
	float radius;
};