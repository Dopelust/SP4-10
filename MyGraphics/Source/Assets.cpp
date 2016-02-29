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

#include "Utility.h"

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
	texture["Tile Occlusion"] = new Texture("Assets//tile_occlusion.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	sprite["Tile Occlusion"] = new Spritesheet();
	GenerateSprites("Tile Occlusion", 9, 3);

	texture["Vignette"] = new Texture("Assets//vignette.tga", GL_LINEAR, GL_LINEAR);
	texture["Vignette2"] = new Texture("Assets//vignette2.tga", GL_LINEAR, GL_LINEAR);

	texture["Loading"] = new Texture("Assets//loading.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);

	texture["Burst"] = new Texture("Assets//burst.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Dispenser"] = new Texture("Assets//watergun.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Fountain"] = new Texture("Assets//fountain.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Sniper"] = new Texture("Assets//sniper.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Water"] = new Texture("Assets//water.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Bubble"] = new Texture("Assets//bubble.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Occlusion"] = new Texture("Assets//occlusion.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Bubble Blower"] = new Texture("Assets//archer.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	texture["Range"] = new Texture("Assets//range_indicator.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);

	texture["Puff"] = new Texture("Assets//puff.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	sprite["Puff"] = new Spritesheet();
	animator["Puff"] = new Animator();
	GenerateSpriteStrip("Puff", 10);
	animator["Puff"]->AddAnimation("Puff", CreateAnimationStrip("Puff", "Puff", 10, 0.02f));

	texture["Splash"] = new Texture("Assets//splash.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	sprite["Splash"] = new Spritesheet();
	animator["Splash"] = new Animator();
	GenerateSpriteStrip("Splash", 5);
	animator["Splash"]->AddAnimation("Splash", CreateAnimationStrip("Splash", "Splash", 5, 0.05f));

	texture["Jellies"] = new Texture("Assets//JellySpriteSheet.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	sprite["Jellies"] = new Spritesheet();
	animator["Jellies"] = new Animator();

	for (int i = 0; i < 11; ++i)
		GenerateSprites("Jellies", 2, 11, 11 * i);
	for (int i = 0; i < 11; ++i)
	{
		animation["Jellies" + ToString(i + 1)] = new Animation();
		CreateAnimationStrip(("Jellies" + ToString(i + 1)).c_str(), "Jellies", 2, 0.2f, 2 * i);
		animator["Jellies"]->AddAnimation(("Jellies" + ToString(i + 1)).c_str(), animation["Jellies" + ToString(i + 1)]);
	}

	texture["Wings"] = new Texture("Assets//wings.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	sprite["Wings"] = new Spritesheet();
	animator["Wings"] = new Animator();
	GenerateSpriteStrip("Wings", 3);
	animator["Wings"]->AddAnimation("Wings", CreateAnimationStrip("Wings", "Wings", 3, 0.125f));
	animation["Wings"]->AddFrame(sprite["Wings"]->GetSprite(1));

	texture["NightChanges"] = new Texture("Assets//Menu.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);

	texture["Rank"] = new Texture("Assets//rank.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	sprite["Rank"] = new Spritesheet();
	GenerateSpriteStrip("Rank", 5);

	texture["Tileset"] = new Texture("Assets//tileset.tga", GL_NEAREST, GL_NEAREST_MIPMAP_LINEAR);
	sprite["Tileset"] = new Spritesheet();
	GenerateSprites("Tileset", 5, 3);
}

Animation * Assets::CreateAnimationStrip(const char* name, const char* spriteSheet, int framecount, float framerate, int offset)
{
	animation[name] = new Animation();

	for (int i = offset; i < offset + framecount; ++i)
		animation[name]->AddFrame(sprite[spriteSheet]->GetSprite(i));

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