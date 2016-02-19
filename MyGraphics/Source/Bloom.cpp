#include "Bloom.h"
#include "FBO.h"
#include "Shader.h"
#include "GraphicsEngine.h"
#include "Mesh.h"
#include "Texture.h"

#include "LUAEngine.h"

void Bloom::Init()
{
	if (LUA.Load("Data//properties.lua"))
	{
		enabled = LUA.GetGlobalNumber("BLOOM_ENABLED");
		intensity = LUA.GetGlobalNumber("BLOOM_INTENSITY");
		radius = LUA.GetGlobalNumber("BLOOM_RADIUS");
		amount = LUA.GetGlobalNumber("BLOOM_AMOUNT");
	}

	shader = Graphics.GetShader("Bloom");

	shader->Use();
	shader->SetUniform1i("colorTexture", 0);
	shader->SetUniform1i("blurTexture", 1);
}

void Bloom::Exit()
{
	if (LUA.Load("Data//properties.lua"))
	{
		LUA.SetGlobalNumber("BLOOM_ENABLED", enabled);
		LUA.SetGlobalNumber("BLOOM_INTENSITY", intensity);
		LUA.SetGlobalNumber("BLOOM_RADIUS", radius);
		LUA.SetGlobalNumber("BLOOM_AMOUNT", amount);
	}
}

Texture * Bloom::Pass(Texture * input)
{
	if (enabled)
	{
		fbo->BindForWriting();
		fbo->SetDrawBuffer(attachment);

		shader->Use();
		shader->SetUniform1f("intensity", intensity);
		shader->SetUniform1f("amount", amount);

		input->Bind();

		fbo->Render();

		return Graphics.Combine(input, Graphics.GaussianBlur(fbo->GetActiveTexture(), radius, true));
	}

	return input;
}

void Bloom::SetRadius(float radius)
{
	this->radius = radius;
}

void Bloom::SetIntensity(float intensity)
{
	this->intensity = intensity;
}

void Bloom::SetAmount(float amount)
{
	this->amount = amount;
}

Bloom::Bloom() : intensity(1), radius(0), amount(1)
{
}

Bloom::~Bloom()
{
}
