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
		flying(false),
		hits(0)
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
	bool flying;
	int hits;

	inline void Set(string name, int tier, float movementSpeed, int split, bool flying, int hits)
	{
		this->name = name;
		this->tier = tier;
		this->movementSpeed = movementSpeed;
		this->split = split;
		this->flying = flying;
		this->hits = hits;
	}
};


#endif