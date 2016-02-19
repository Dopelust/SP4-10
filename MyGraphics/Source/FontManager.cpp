#include "FontManager.h"
#include "Assets.h"
#include "Mesh2D.h"
#include "Texture.h"

FontManager::FontManager() 
{
}

FontManager::~FontManager()
{
}

void FontManager::Init()
{
	Texture* fontMap = new Texture("Assets//Font//BtR.tga", GL_LINEAR, GL_LINEAR);
	//fontMap->MaxAnisotropy();

	font[MINECRAFT].Load("Assets//Font//BtR.fnt");	
	font[MINECRAFT].SetFontMap(fontMap);
}

#include "Shader.h"
static const float inverse255 = 1.0f / 255;

void FontManager::ImmediateDraw(string text, float Tx, float Ty, float Sxy, int R, int G, int B, int A, fontType id)
{
	Resource.GetShader("Font")->Use();
	font[id].Draw(text, Tx, Ty, Sxy * 4, Vector4(R * inverse255, G * inverse255, B * inverse255, A * inverse255));
	font[id].Render();
}

void FontManager::Draw(string text, float Tx, float Ty, float Sxy, int R, int G, int B, int A, fontType id)
{
	font[id].Draw(text, Tx, Ty, Sxy * 4, Vector4(R * inverse255, G * inverse255, B * inverse255, A * inverse255));
}

void FontManager::Draw(string text, const Mtx44 & M, const Vector4 & RGBA, fontType id)
{
	font[id].Draw(text, M, RGBA);
}

#include "GraphicsEngine.h"

void FontManager::Render()
{
	Resource.GetShader("Font")->Use();
	Graphics.UpdateV(Resource.GetShader("Font"), true);

	for (auto& text : font)
	{
		text.Render();
	}
}

FontManager& FontManager::Instance()
{
	static FontManager font;
	return font;
}

Font * FontManager::GetFont(fontType id)
{
	return &font[id];
}
