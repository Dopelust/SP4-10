#include "TextRenderer2D.h"
#include "../../../FontManager.h"

FontManager* TextRenderer2D::font = &FontManager::Instance();

TextRenderer2D::TextRenderer2D()
{
}

TextRenderer2D::~TextRenderer2D()
{
}

FontManager* TextRenderer2D::GetFont()
{
	return font;
}

void TextRenderer2D::SetText(const char * text)
{
	this->text = text;
}

void TextRenderer2D::Draw(const Mtx44 & parent)
{
	if (alignCenter)
	{
		Mtx44 T;
		T.SetToTranslation(-font->GetFont()->GetTextSize(text).x * 0.5f, 0, 0);
		font->Draw(text, parent * T, color);
	}
	else
		font->Draw(text, parent, color);
}
