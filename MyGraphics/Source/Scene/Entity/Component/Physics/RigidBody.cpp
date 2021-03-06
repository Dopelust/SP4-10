#include "RigidBody.h"
#include "../Transform.h"
#include "../../Entity.h"
#include "../../../../InputHandler.h"
#include "BoxCollider.h"

RigidBody::RigidBody() : transform(NULL), box(NULL), mass(0), friction(1), bounceFactor(0), gravityScale(1), ignoreCollisions(false)
{
}

RigidBody::~RigidBody()
{
}

Vector3 RigidBody::GetHorizontalVelocity()
{
	return Vector3(velocity.x, 0, velocity.z);
}

void RigidBody::ApplyForce(const Vector3& force)
{
	velocity += force;
}

void RigidBody::Init(Entity * ent)
{
	owner = ent;
	transform = ent->transform;
	box = ent->GetComponent<BoxCollider>();
}
	
void RigidBody::Update(double dt)
{
	if (gravityScale)
	{
		velocity.x += -velocity.x * mass * friction * dt;
		velocity.z += -velocity.z * mass * friction * dt;

		velocity.y += -9.8f * mass * gravityScale * dt;
	}
	else
	{
		velocity += -velocity * mass * friction * dt;
	}

	lastposition = transform->GetPosition();
	transform->Position() += velocity * dt;
}

#include "../../../../Partition.h"
#include "../../../../Cell.h"
#include "../../../../Grid.h"
#include "../../../../CollisionQuery.h"
#include <functional>

struct CollisionEntry
{
	Vector3 min;
	Vector3 max;
	Entity* entity{ NULL };
};


#include "../../Collision.h"

void RigidBody::ResolveCollisions()
{
	for (auto& cell : box->GetPartitions())
	{
		for (auto& entity : cell->GetEntities())
		{
			if (entity == owner)
				continue;

			if (CollisionQuery::Test(box, entity->GetComponent<BoxCollider>()))
			{
				owner->OnCollisionEnter(Collision(Collision::UNDEFINED, entity));
			}
		}
	}

	Vector2& position = Grid::GetIndex(transform->GetPosition()).GetVector2();

	for (int i = Math::Max(0, (int)position.x - 1); i <= Math::Min(NumberOfTilesX, (int)position.x + 1); ++i)
	for (int j = Math::Max(0, (int)position.y - 1); j <= Math::Min(NumberOfTilesY, (int)position.y + 1); ++j)
	{
		switch (box->GetCell()->GetTile(i, j).index)
		{
		case 2:
			if (CollisionQuery::Test(box, box->GetCell()->GetTileMinCoord(i, j), box->GetCell()->GetTileMaxCoord(i, j)))
				owner->OnCollisionEnter(Collision(Collision::UNDEFINED, NULL));
			break;
		}
	}
}

Vector3 RigidBody::GetLastMaxCoord()
{
	return lastposition + box->offset + box->size * 0.5f;
}

Vector3 RigidBody::GetLastMinCoord()
{
	return lastposition + box->offset - box->size * 0.5f;
}
