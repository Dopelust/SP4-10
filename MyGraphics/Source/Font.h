#pragma once

#include "DrawInstance2D.h"
#include "Vector4.h"
#include "Mtx44.h"

#include <string>
using namespace::std;

struct Character
{
	Vector2 min;
	Vector2 max;
	Vector2 offset;
	Vector2 size;
	float advance;

	float GetWidth();
	float GetHeight();
};

class FontManager;
class Texture;
class Font
{
public:
	Vector2 GetTextSize(const string& text);

	void Draw(string text, float Tx, float Ty, float S, const Vector4& RGBA);
	void Draw(string text, const Mtx44& M, const Vector4& RGBA);

	void Render();
	
private:
	friend FontManager;

	Font();
	~Font();
	void Load(const char* filepath);
	void SetFontMap(Texture* texture);

	Texture* fontMap;
	DrawInstance2D instance;
	Character character[255];
};