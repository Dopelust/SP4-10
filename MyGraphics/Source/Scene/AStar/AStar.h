#pragma once

#include "Path.h"

#include <vector>
using namespace::std;

struct Vector2;

class AStar
{
public:
	static const int dir = 4; // number of possible directions to go at any position

	static void Update(const vector<vector<bool>>& tileMap);
	static Path GetPath(const Vector2& s, const Vector2& g);

private:
	static vector<vector<bool>> tileMap;
	static vector<vector<bool>> openMap;
	static vector<vector<bool>> closeMap;
	static vector<vector<int>> dirMap;

	static int row;
	static int col;
};