#pragma once

#include "Shader.h"

#include <string>
using namespace::std;

class Assets;
class GraphicsEngine;
class ShaderManager
{
private:
	friend GraphicsEngine;
	friend Assets;

	ShaderManager();
	~ShaderManager();

	static ShaderManager& Instance();

	void Init();
	Shader* GetCurrentShader();

	map<string, Shader*> shader;
	void Flush();
};