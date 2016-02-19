#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include "Sprite.h"

#include <vector>
#include <string>
using namespace::std;

class Assets;
class Spritesheet
{
public:
	Sprite* AddSprite();
	Sprite* GetSprite(int i);

private:
	friend Assets;

	Spritesheet();
	~Spritesheet();

	vector<Sprite> sprite;
};

#endif