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
	void SetName(const char* name);

private:
	Entity* owner;
	RigidBody* rigid;

	// Projectile texture
	string name;
	int pierceCount;

	TowerData* towerData;

	// store the id of entities that it pierced so that it will not pierce its children when popped
	vector<int> pierced;
};

#endif