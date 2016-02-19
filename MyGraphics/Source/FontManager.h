#pragma once

#include "Font.h"

#include <string>
using namespace::std;

class FontManager
{
public:
	enum fontType
	{
		MINECRAFT,
		NUM_FONTS,
	};

	void Init();

	void ImmediateDraw(string text, float Tx, float Ty, float Sxy, int R = 255, int G = 255, int B = 255, int A = 255, fontType id = MINECRAFT);
	void Draw(string text, float Tx, float Ty, float Sxy, int R = 255, int G = 255, int B = 255, int A = 255, fontType id = MINECRAFT);
	void Draw(string text, const Mtx44& M, const Vector4& RGBA, fontType id = MINECRAFT);

	void Render();

	static FontManager& Instance();
	Font* GetFont(fontType id = MINECRAFT);
private:
	FontManager();
	~FontManager();

	Font font[NUM_FONTS];
};