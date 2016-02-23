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
	cost(-1),
	range(-1),
	cooldown(-1),
	pierce(-1),
	speed(-1),
	eDamage(-1),
	eDuration(-1),
	shot(1),
	textureName(""),
	projectileName(""),
	description("")
	{

	}

	inline void Set(int cost, float eDamage, float eDuration, int range, float cooldown, int shot, int pierce, float speed, string textureName, string projectileName, string description)
	{
		this->cost = cost;
		this->eDamage = eDamage;
		this->eDuration = eDuration;
		this->range = range;
		this->cooldown = cooldown;
		this->pierce = pierce;
		this->shot = shot;
		this->speed = speed;
		this->textureName = textureName;
		this->projectileName = projectileName;
		this->description = description;
	}

	int cost = -1;
	int range = -1;
	float eDamage = -1;
	float eDuration = -1;
	float cooldown = -1;
	int pierce;
	float speed;
	int shot;
	string textureName = ""; 
	string projectileName = "";
	string description = "";
};


#endif