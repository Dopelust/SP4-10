#ifndef TOWER_DATA_H
#define TOWER_DATA_H

#include <string>
#include <map>

using std::string;
using std::map;

// Texture file path format:

struct TowerData
{
	TowerData() :
	name(""),
	cost(-1),
	range(-1),
	cooldown(-1),
	textureName(""),
	projectileName(""),
	description("")
	{

	}

	inline void Set(string name, int cost, int range, float cooldown, string textureName, string projectileName, string description)
	{
		this->name = name;
		this->cost = cost;
		this->range = range;
		this->cooldown = cooldown;
		this->textureName = textureName;
		this->projectileName = projectileName;
		this->description = description;
	}

	string name = "";
	int cost = -1;
	int range = -1;
	float cooldown = -1;
	string textureName = ""; 
	string projectileName = "";
	string description = "";
};


#endif