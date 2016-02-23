#ifndef PROJECTILE_CONTROLLER_H
#define PROJECTILE_CONTROLLER_H

#include "../Component.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class ProjectileData;
struct TowerData;
class RigidBody;
class TowerController;
struct Vector2;

class Projectile : public Component
{
public:
	Projectile();
	~Projectile();

	void Init(Entity* ent);
	void LateInit(string type);
	void SetProperties(TowerData *towerData, Vector2 velocity, float rotation);
	void Update(double dt);
	void OnCollisionEnter(const Collision& col);
	void SetType(const char* type);

	int pierce;
	float speed;

	ProjectileData& GetData();
	int GetEffect();
	float GetSpeed();
	int GetPierce();

	vector<int> pierced;

private:
	Entity* owner;
	RigidBody* rigid;

	string type;
};

#endif