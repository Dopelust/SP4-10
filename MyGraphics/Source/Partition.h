#pragma once

#include "GridInfo.h"
#include "Vector3.h"

#include <vector>
using namespace::std;

class Entity;

class Partition
{
public:
	Partition(float x, float y);
	~Partition();

	void Add(Entity* entity);
	void Remove(Entity* entity);

	void Reset();
	const vector<Entity*>& GetEntities();

private:
	vector<Entity*> entityList;
	Vector3 min, max;
};
