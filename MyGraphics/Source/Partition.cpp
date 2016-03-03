#include "Partition.h"

#include <algorithm>
using namespace::std;

Partition::Partition(float x, float y)
{
	min.Set(x, y);
	max.Set(x + PartitionWidth, y + PartitionHeight); 
}

Partition::~Partition()
{
}

void Partition::Add(Entity* entity)
{
	entityList.push_back(entity);
}

void Partition::Remove(Entity * entity)
{
	auto it = find(entityList.begin(), entityList.end(), entity);

	if (it != entityList.end())
		entityList.erase(it);
}

void Partition::Reset()
{
	entityList.clear();
}

const vector<Entity*>& Partition::GetEntities()
{
	return entityList;
}