#pragma once

#include "Vector2.h"

#include <vector>
using namespace::std;

class AStar;

class Path
{
public:
	int GetPathLength();
	Vector2 GetPath(int index);

private:
	friend AStar;
	
	vector<Vector2> path;
	void AddToPath(const Vector2& path);
};