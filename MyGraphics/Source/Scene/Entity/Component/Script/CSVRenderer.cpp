#include "CSVRenderer.h"

CSVRenderer::CSVRenderer() : sprite(NULL)
{
}

CSVRenderer::~CSVRenderer()
{
}

#include "../../Entity.h"
#include "../Transform.h"

void CSVRenderer::Init(Entity * ent)
{
	transform = ent->transform;
}

void CSVRenderer::SetIndividualSize(int width, int height)
{
	this->width = width;
	this->height = height;

	transform->Size().x = width * csv[0].size();
	transform->Size().y = height * csv.size();
}

#include "FileSystem.h"
#include "Utility.h"

void CSVRenderer::UploadCSV(const char * filepath)
{
	for (auto& c : csv)
		c.clear();

	csv.clear();

	if (!File.Exists(filepath))
		return;

	vector<string>& lines = File.GetLines(filepath);

	for (int y = 0; y < lines.size(); ++y)
	{
		vector<float>& tiles = VectorStoF(ParseLine(lines[lines.size() - 1 - y], ","));
		csv.push_back(vector<int>());

		for (int x = 0; x < tiles.size(); ++x)
		{
			csv[y].push_back(tiles[x]);
		}
	}

	UpdateSize();
}

void CSVRenderer::UpdateSize()
{
	if (csv.empty())
	{
		width = 0;
		height = 0;
	}
	else
	{
		width = transform->GetSize().x / csv[0].size();
		height = transform->GetSize().y / csv.size();
	}
}

void CSVRenderer::SetSpritesheet(Spritesheet * sprite)
{
	this->sprite = sprite;
}

#include "../../../../Spritesheet.h"
#include "../../../../Sprite.h"

void CSVRenderer::Draw(const Mtx44 & parent)
{
	if (sprite && csv.size())
	{
		Mtx44& T = parent * transform->S().GetInverse();

		int yNum = csv.size();
		int xNum = csv[0].size();

		float tHeight = height * yNum * 0.5f;
		float tWidth = width * xNum * 0.5f;

		for (int y = 0; y < csv.size(); ++y)
		{
			for (int x = 0; x < csv[y].size(); ++x)
			{
				Mtx44& mtx = T * Mtx44::GetTransformation(x * width - tWidth, y * height - tHeight, 0, width, height);
				sprite->GetSprite(csv[y][x])->Render(mtx, color, layer);

				if (csv[y][x] != 2)
				{
					if (y + 1 < yNum && csv[y + 1][x] == 2)
						DrawOcclusion(mtx, 7);
					if (y - 1 >= 0 && csv[y - 1][x] == 2)
						DrawOcclusion(mtx, 1);
					if (x + 1 < xNum && csv[y][x + 1] == 2)
						DrawOcclusion(mtx, 3);
					if (x - 1 >= 0 && csv[y][x - 1] == 2)
						DrawOcclusion(mtx, 5);

					if (y + 1 < yNum && x + 1 < xNum && csv[y + 1][x + 1] == 2)
						DrawOcclusion(mtx, 6);
					if (y + 1 < yNum && x - 1 >= 0 && csv[y + 1][x - 1] == 2)
						DrawOcclusion(mtx, 8);
					if (y - 1 >= 0 && x + 1 < xNum && csv[y - 1][x + 1] == 2)
						DrawOcclusion(mtx, 0);
					if (y - 1 >= 0 && x - 1 >= 0 && csv[y - 1][x - 1] == 2)
						DrawOcclusion(mtx, 2);
				}
			}
		}
	}
}

#include "../../../../Assets.h"

void CSVRenderer::DrawOcclusion(const Mtx44& mtx, int orientation)
{
	Sprite* sprite = Resource.GetSpritesheet("Tile Occlusion")->GetSprite(orientation);
	sprite->Render(mtx, Vector4(0.15f, 0.15f, 0.15f), layer);
}
