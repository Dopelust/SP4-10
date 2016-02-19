#include "Tile.h"

#include <algorithm>
using namespace::std;

Tile::Tile() : index(0)
{
}

Tile::~Tile()
{
}

#include "Mesh2D.h"
#include "Assets.h"

#include "Spritesheet.h"
#include "Sprite.h"

void Tile::Draw(int i, int j)
{
	Sprite* sprite = Resource.GetSpritesheet("Tileset")->GetSprite(index);
	Quad.GetInstance(sprite->GetTexture()).Add(Mtx44::GetTransformation(i * TileWidth, j * TileHeight, 0, TileWidth, TileHeight), Vector4(1,1,1), sprite->GetUV());
}