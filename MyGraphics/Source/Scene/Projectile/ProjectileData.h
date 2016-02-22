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
		pierce(0),
		speed(0),
		distance(0),
		effect(ProjectileEffect::NONE)
	{

	}

	~ProjectileData()
	{

	}

	string name;
	int pierce;
	float speed;
	float distance;
	ProjectileEffect effect;

	inline void Init(string name, ProjectileEffect effect)
	{
		this->name = name;
		this->effect = effect;
	}

	inline void Set(int pierce, float speed, float distance)
	{
		this->pierce = pierce;
		this->speed = speed;
		this->distance = distance;
	}
};


#endif