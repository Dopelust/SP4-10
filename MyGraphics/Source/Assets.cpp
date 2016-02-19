#include "Assets.h"
#include "MeshBuilder.h"
#include "Texture.h"
#include "Spritesheet.h"
#include "Animation.h"
#include "Animator.h"
#include "Utility.h"
#include "GraphicsEngine.h"
#include "ShaderManager.h"
#include "Shader.h"

Assets& Assets::Instance()
{
	static Assets assets;
	return assets;
}

Shader * Assets::GetShader(const char * key)
{
	return shader.shader[key];
}

Mesh * Assets::GetMesh(const char * key)
{
	return mesh[key];
}

Texture * Assets::GetTexture(const char * key)
{
	return texture[key];
}

Spritesheet * Assets::GetSpritesheet(const char * key)
{
	return sprite[key];
}

Animation * Assets::GetAnimation(const char * key)
{
	return animation[key];
}

Animator * Assets::GetAnimator(const char * key)
{
	return animator[key];
}

Assets::Assets() : shader(ShaderManager::Instance())
{
}

Assets::~Assets()
{
	for (auto& m : mesh)
		delete m.second;
	for (auto& t : texture)
		delete t.second;
	for (auto& s : sprite)
		delete s.second;
}

void Assets::Init()
{
	shader.Init();

	//Mesh
	mesh["wire"] = MeshBuilder::GenerateCubeOutline(Vector3(1, 1, 1), 1, 1, 1);
	mesh["quad"] = MeshBuilder::GenerateVerticalQuad(Vector3(1, 1, 1), 1, 1);
	mesh["cube"] = MeshBuilder::GenerateCube(Vector3(1, 1, 1), 1, 1, 1);
	mesh["line"] = MeshBuilder::GenerateLine(Vector3(1, 1, 1), 1.f);
	mesh["ray"] = MeshBuilder::GenerateRay(Vector3(1, 1, 1), 1);
	mesh["sphere"] = MeshBuilder::GenerateSphere(Vector3(1, 1, 1), 20, 20, 1);

	//Texture
	texture["Circle"] = new Texture("Assets//circle.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Range"] = new Texture("Assets//range_indicator.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);

	texture["Tileset"] = new Texture("Assets//tileset.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);

	sprite["Tileset"] = new Spritesheet();

	for (int i = 0; i < 5; ++i)
	{
		Sprite* s = sprite["Tileset"]->AddSprite();
		Vector4 uv = Texture::GetUV(i, 3);

		s->SetUV(uv);
		s->SetTexture(texture["Tileset"]);
	}

	texture["Girl"] = new Texture("Assets//girl.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Girl"]->MaxAnisotropy();

	sprite["Girl"] = new Spritesheet();
	animation["Girl"] = new Animation();
	animator["Girl"] = new Animator();

	for (int i = 0; i < 4; ++i)
	{
		Sprite* s = sprite["Girl"]->AddSprite();
		Vector4 uv = Texture::GetUV(i, 4);
		uv.y = 0;
		uv.w = 1;

		s->SetUV(uv);
		s->SetTexture(texture["Girl"]);
	}

	for (int i = 0; i < 4; ++i)
		animation["Girl"]->AddFrame(sprite["Girl"]->GetSprite(i));
	animation["Girl"]->SetFramerate(0.1f);

	animator["Girl"]->AddAnimation("Move", animation["Girl"]);
}