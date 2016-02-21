#ifndef PROJECITLE_DATA_H
#define PROJECTILE_DATA_H

#include <string>
#include <map>

using std::string;
using std::map;

class ProjectileData
{
public:
	enum ProjectileEffect
	{
		NONE,
		NORMAL,
		SLOW,
		STUN,
		MAX_EFFECT
	};

	ProjectileData() :
		name(""),
		speed(0),
		distance(0),
		pierce(0),
		effect(ProjectileEffect::NONE)
	{

	}

	~ProjectileData()
	{

	}

	string name;
	float speed;
	float distance;
	int pierce;
	ProjectileEffect effect;

	inline void Set(string name, float speed, float distance, int pierce, ProjectileEffect effect)
	{
		this->name = name;
		this->speed = speed;
		this->distance = distance;
		this->pierce = pierce;
		this->effect = effect;
	}
};


#endif