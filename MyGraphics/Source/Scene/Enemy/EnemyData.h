#ifndef ENEMY_DATA_H
#define ENEMY_DATA_H

#include <string>
#include <map>

using std::string;
using std::map;

class EnemyData
{
public:
	EnemyData() :
		name(""),
		tier(0),
		movementSpeed(0),
		split(0),
		index(0)
	{

	}

	~EnemyData()
	{

	}

	string name;
	int tier;
	float movementSpeed;
	int split;
	int index;

	inline void Set(string name, int tier, float movementSpeed, int split, int index)
	{
		this->name = name;
		this->tier = tier;
		this->movementSpeed = movementSpeed;
		this->split = split;
		this->index = index;
	}
};


#endif