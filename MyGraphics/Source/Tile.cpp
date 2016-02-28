#include "Tile.h"

#include <algorithm>
using namespace::std;

Tile::Tile() : index(0)
{
}

Tile::~Tile()
{
}

#include "Assets.h"

#include "Spritesheet.h"
#include "Sprite.h"

#include "Mtx44.h"

Mtx44 Tile::GetTransformation(int i, int j)
{
	return Mtx44::GetTransformation(i * TileWidth, j * TileHeight, 0, TileWidth, TileHeight);
}

void Tile::Draw(const Mtx44 & mtx)
{
	Sprite* sprite = Resource.GetSpritesheet("Tileset")->GetSprite(index);
	sprite->Render(mtx, Vector4(1, 1, 1), 0);
}

void Tile::DrawOcclusion(const Mtx44 & mtx, int orientation)
{
	Sprite* sprite = Resource.GetSpritesheet("Tile Occlusion")->GetSprite(orientation);
	sprite->Render(mtx, Vector4(0.15f, 0.15f, 0.15f), 0);
}