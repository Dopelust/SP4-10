#include "BoxCollider.h"
#include "../../Entity.h"
#include "../Transform.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::~BoxCollider()
{
}

Vector3 BoxCollider::GetMinCoord()
{
	return transform->GetPosition() + offset - size * 0.5f;
}

Vector3 BoxCollider::GetMaxCoord()
{
	return transform->GetPosition() + offset + size * 0.5f;
}

void BoxCollider::Init(Entity * ent)
{
	transform = ent->transform;
}

const vector<Partition*>& BoxCollider::GetPartitions()
{
	return part;
}

Cell* BoxCollider::GetCell()
{
	return cell;
}