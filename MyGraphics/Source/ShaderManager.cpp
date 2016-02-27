#include "ShaderManager.h"
#include "MyMath.h"

#include <vector>

ShaderManager& ShaderManager::Instance()
{
	static ShaderManager shader;
	return shader;
}

void ShaderManager::Flush()
{
	for (auto& s : shader)
		s.second->Flush();
}

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	for (auto& s : shader)
		delete s.second;
}

void ShaderManager::Init()
{
	cout << "Unpacking Shaders... ";

	shader["FBO"] = new Shader();
	shader["FBO"]->Load("Shader//Framebuffer.vertexshader", "Shader//Framebuffer.fragmentshader");

	shader["Forward"] = new Shader();
	shader["Forward"]->Load("Shader//Main.vertexshader", "Shader//Main.fragmentshader");
	shader["Forward"]->InformV();
	shader["Forward"]->InformP();

	shader["Gaussian"] = new Shader();
	shader["Gaussian"]->Load("Shader//Framebuffer.vertexshader", "Shader//Gaussian.fragmentshader");

	shader["Combine"] = new Shader();
	shader["Combine"]->Load("Shader//Framebuffer.vertexshader", "Shader//Combine.fragmentshader");
	
	shader["Combine"]->Use();
	shader["Combine"]->SetUniform1i("texture_one", 0);
	shader["Combine"]->SetUniform1i("texture_two", 1);

	shader["Bloom"] = new Shader();
	shader["Bloom"]->Load("Shader//Framebuffer.vertexshader", "Shader//Bloom.fragmentshader");

	shader["Font"] = new Shader();
	shader["Font"]->Load("Shader//2D.vertexshader", "Shader//Text.fragmentshader");
	shader["Font"]->InformOrtho();

	shader["2D"] = new Shader();
	shader["2D"]->Load("Shader//2D.vertexshader", "Shader//2D.fragmentshader");
	shader["2D"]->InformOrtho();

	cout << "[DONE]" << endl << endl;
}

Shader * ShaderManager::GetCurrentShader()
{
	return Shader::shader;
}
