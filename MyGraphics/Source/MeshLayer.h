#pragma once

#include <vector>
#include <map>
using namespace::std;

#include "DrawInstance2D.h"

class Texture;

class MeshLayer
{
public:
	MeshLayer() {}
	~MeshLayer() {}

	vector<Texture*> instances;
	map<Texture*, DrawInstance2D> instanceMap;
};