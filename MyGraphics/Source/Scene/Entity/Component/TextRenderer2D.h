#pragma once

#include "Component.h"
#include "Vector4.h"

#include <string>
using namespace::std;

class FontManager;
class Texture;
class TextRenderer2D : public Component
{
public:
	TextRenderer2D();
	~TextRenderer2D();

	void SetAlignCenter(bool alignCenter);

	void SetText(const char* text);
	void SetColor(float r, float g, float b, float a = 1);

	FontManager* GetFont();
	const Vector4& GetColor();

protected:
	static FontManager* font;

	string text;
	Vector4 color;

	bool alignCenter;
	void Draw(const Mtx44& parent);
};