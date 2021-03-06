#pragma once

#include <string>
#include <map>
using namespace::std;

class ShaderManager;
class Shader;

class Animator;
class Animation;
class Spritesheet;
class Mesh;
class Texture;
class GraphicsEngine;

#define Resource Assets::Instance()

class Assets
{
public:
	static Assets& Instance();

	Shader* GetShader(const char* key);
	Mesh* GetMesh(const char* key);
	Texture* GetTexture(const char* key);
	Spritesheet* GetSpritesheet(const char* key);
	Animation* GetAnimation(const char* key);
	Animator* GetAnimator(const char* key);

private:
	friend GraphicsEngine;

	Assets();
	~Assets();

	void Init();

	ShaderManager& shader;

	map<string, Mesh*> mesh;
	map<string, Texture*> texture;
	map<string, Spritesheet*> sprite;
	map<string, Animation*> animation;
	map<string, Animator*> animator;

	Animation* CreateAnimationStrip(const char* name, const char* spriteSheet, int framecount, float framerate, int offset = 0);

	void GenerateSprites(const char* name, int count, int rows, int offset = 0);
	void GenerateSpriteStrip(const char* name, int count);
};