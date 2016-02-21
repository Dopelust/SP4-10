#ifndef PROJECTILE_CONTROLLER_H
#define PROJECTILE_CONTROLLER_H

#include "../Component.h"

#include <string>

using std::string;

class ProjectileData;
class RigidBody;
class TowerController;
struct Vector2;

class Projectile : public Component
{
public:
	Projectile();
	~Projectile();

	void Init(Entity* ent);
	void LateInit(string type, Vector2 velocity, float rotation);
	void Update(double dt);
	void OnCollisionEnter(const Collision& col);
	void SetType(const char* type);

	float distTravelled;
	int pierce;

	ProjectileData& GetData();
	int GetEffect();
	float GetSpeed();
	float GetDistance();
	int GetPierce();

private:
	Entity* owner;
	RigidBody* rigid;

	string type;
};

#endif