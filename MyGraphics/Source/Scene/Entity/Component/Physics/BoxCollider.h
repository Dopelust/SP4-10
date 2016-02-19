#pragma once

#include "../Component.h"
#include "Vector2.h"
#include "Vector3.h"

#include <vector>
using namespace::std;

class Cell;
class RigidBody;
class Grid;
class Transform;
class BoxCollider : public Component
{
public:
	BoxCollider();
	~BoxCollider();

	Vector3 GetMinCoord();
	Vector3 GetMaxCoord();

	Vector3 size;
	Vector3 offset;

	void Init(Entity* ent);

//	void Draw(const Mtx44& parent);

	const vector<Cell*>& GetCells();

private:
	friend Grid;
	friend RigidBody;

	Transform* transform;
	vector<Cell*> cells;
};