#pragma once

#include "Graphic2D.h"

#include <string>
using namespace::std;

class FontManager;
class Texture;
class TextRenderer2D : public Graphic2D
{
public:
	TextRenderer2D();
	~TextRenderer2D();

	void SetText(const char* text);

	FontManager* GetFont();

protected:
	static FontManager* font;

	string text;
	void Draw(const Mtx44& parent);
};