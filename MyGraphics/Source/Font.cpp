#include "Font.h"
#include "Texture.h"
#include "Mesh2D.h"

Font::Font() : fontMap(NULL)
{
}

Font::~Font()
{
	if (fontMap)
		delete fontMap;
}

#include <fstream>
#include <sstream>

bool IsDash(char a)
{
	return a == '-';
}

bool IsInteger(char a)
{
	for (char i = '0'; i <= '9'; ++i)
	{
		if (a == i)
			return true;
	}

	return false;
}

vector<string> Parse(string line)
{
	vector<string> tokens;
	string token;
	stringstream ss(line);

	for (int i = 0; i < line.size(); ++i)
	{
		if ((i + 1 < line.size() && IsDash(line[i]) && IsInteger(line[i + 1]))
			|| IsInteger(line[i]))
		{
			token += line[i];
			++i;

			for (int j = i; j < line.size(); ++j, ++i)
			{
				if (IsInteger(line[j]))
				{
					token += line[j];
				}
				else
				{
					tokens.push_back(token);
					token = "";
					break;
				}
			}
		}
		else
			continue;
	}

	if (!token.empty())
		tokens.push_back(token);

	return tokens;
}

void Font::Load(const char * filepath)
{
	ifstream inData;
	string data;
	inData.open(filepath);

	int line = 1;
	while (!inData.eof())
	{
		getline(inData, data);

		if (data == "")
			continue;

		if (line > 4)
		{
			vector<string>& tokens = Parse(data);

			if (tokens.size() == 10)
			{
				float data[10];
				for (int i = 0; i < 10; ++i)
					data[i] = stoi(tokens[i]);

				character[(int)data[0]].min.Set(data[1] / 512, (512 - data[4] - data[2]) / 512);
				character[(int)data[0]].max.Set((data[3] + data[1]) / 512, (512 - data[2]) / 512);
				character[(int)data[0]].offset.Set(data[5] / 512, data[6] / 512);
				character[(int)data[0]].advance = data[7] / 512;
			}
		}

		++line;
	}

	inData.close();
}

void Font::SetFontMap(Texture * texture)
{
	this->fontMap = texture;
}

Vector2 Font::GetTextSize(const string & text)
{
	Vector2 size(0, 0);

	for (unsigned i = 0; i < text.length(); ++i)
	{
		if (text[i] == ' ')
			size.x += 0.0002f;

		size.x += character[text[i]].advance * 0.8f;
		size.y = Math::Max(character[text[i]].GetHeight(), size.y);
	}

	return size;
}

void Font::Draw(string text, float Tx, float Ty, float size, const Vector4& RGBA)
{
	if (text.empty())
		return;

	Mtx44 Txyz, Si, T, Sf;
	float translation = 0;

	Txyz.SetToTranslation(Tx, Ty, 0);
	Si.SetToScale(size, size, 1);

	for (int i = 0; i < text.size(); ++i)
	{
		T.SetToTranslation(translation, 0, 0);
		Sf.SetToScale(character[text[i]].GetWidth(), character[text[i]].GetHeight(), 1);

		instance.Add(Txyz * Si * T * Sf, RGBA, Vector4(character[text[i]].min.x, character[text[i]].min.y, character[text[i]].max.x, character[text[i]].max.y));

		translation += character[text[i]].advance * 0.8f;
	}
}

void Font::Draw(string text, const Mtx44 & M, const Vector4 & RGBA)
{
	if (text.empty())
		return;

	Mtx44 offset;
	offset.SetToTranslation(0, -0.5f, 0);

	Mtx44 T, S;
	float translation = 0;

	for (int i = 0; i < text.size(); ++i)
	{
		T.SetToTranslation(translation, 0, 0);
		S.SetToScale(character[text[i]].GetWidth(), character[text[i]].GetHeight(), 1);

		instance.Add(M * T * S * offset, RGBA, Vector4(character[text[i]].min.x, character[text[i]].min.y, character[text[i]].max.x, character[text[i]].max.y));

		translation += character[text[i]].advance * 0.8f;
	}
}

void Font::Render()
{
	if (instance.NumInstance())
	{
		fontMap->Bind();

		Quad.Render(instance);
		instance.Clear();
	}
}

float Character::GetWidth()
{
	return max.x - min.x;
}

float Character::GetHeight()
{
	return max.y - min.y;
}
