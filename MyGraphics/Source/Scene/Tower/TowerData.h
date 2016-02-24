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
	shot(-1),
	textureName(""),
	projectileName(""),
	projectileEffect(0),
	projectileValue(0),
	effectDuration(0),
	projectileStyle(0),
	description("")
	{

	}

	inline void Set(int cost, int range, float cooldown, int shot, int pierce, float speed, string textureName, int ai, string projectileName, int projectileType, float projectileValue, float effectDuration, int projectileStyle, string description)
	{
		this->cost = cost;
		this->range = range;
		this->cooldown = cooldown;
		this->pierce = pierce;
		this->shot = shot;
		this->speed = speed;
		this->textureName = textureName;
		this->projectileName = projectileName;
		this->projectileEffect = projectileType;
		this->projectileValue = projectileValue;
		this->effectDuration = effectDuration;
		this->projectileStyle = projectileStyle;
		this->description = description;
		this->ai = ai;
	}

	int cost;
	int range;
	float cooldown;
	int pierce;
	float speed;
	int shot;
	string textureName;
	string projectileName;
	int projectileEffect;
	float projectileValue;
	float effectDuration;
	int projectileStyle;
	int ai;
	string description;
};


#endif