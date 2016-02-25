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
	texture["Burst"] = new Texture("Assets//burst.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Dispenser"] = new Texture("Assets//watergun.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Fountain"] = new Texture("Assets//fountain.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Sniper"] = new Texture("Assets//sniper.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Water"] = new Texture("Assets//water.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Bubble"] = new Texture("Assets//bubble.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Occlusion"] = new Texture("Assets//occlusion.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Archer"] = new Texture("Assets//archer.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Circle"] = new Texture("Assets//circle.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Range"] = new Texture("Assets//range_indicator.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);

	texture["Blue"] = new Texture("Assets//blueslime1.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Red"] = new Texture("Assets//redslime.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	
	texture["Puff"] = new Texture("Assets//puff.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	sprite["Puff"] = new Spritesheet();
	animation["Puff"] = new Animation();
	animator["Puff"] = new Animator();
	GenerateSpriteStrip("Puff", 10);
	animator["Puff"]->AddAnimation("Puff", CreateAnimationStrip("Puff", 10, 0.02f));

	texture["Splash"] = new Texture("Assets//splash.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	sprite["Splash"] = new Spritesheet();
	animation["Splash"] = new Animation();
	animator["Splash"] = new Animator();
	GenerateSpriteStrip("Splash", 5);
	animator["Splash"]->AddAnimation("Splash", CreateAnimationStrip("Splash", 5, 0.05f));

	texture["NightChanges"] = new Texture("Assets//Menu.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);

	texture["Rank"] = new Texture("Assets//rank.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	sprite["Rank"] = new Spritesheet();
	GenerateSpriteStrip("Rank", 5);

	texture["Tileset"] = new Texture("Assets//tileset.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	sprite["Tileset"] = new Spritesheet();
	GenerateSprites("Tileset", 5, 3);
}

Animation * Assets::CreateAnimationStrip(const char* name, int framecount, float framerate, int offset)
{
	for (int i = offset; i < offset + framecount; ++i)
		animation[name]->AddFrame(sprite[name]->GetSprite(i));

	animation[name]->SetFramerate(framerate);
	return animation[name];
}

void Assets::GenerateSprites(const char * name, int count, int rows, int offset)
{
	for (int i = offset; i < offset + count; ++i)
	{
		Sprite* s = sprite[name]->AddSprite();
		Vector4 uv = Texture::GetUV(i, rows);

		s->SetUV(uv);
		s->SetTexture(texture[name]);
	}
}

void Assets::GenerateSpriteStrip(const char * name, int count)
{
	for (int i = 0; i < count; ++i)
	{
		Sprite* s = sprite[name]->AddSprite();
		Vector4 uv = Texture::GetUV(i, count);

		uv.y = 0;
		uv.w = 1;

		s->SetUV(uv);
		s->SetTexture(texture[name]);
	}
}