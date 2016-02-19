#pragma once

class Entity;

struct Collision
{
	enum CollisionFace
	{
		UNDEFINED,
		TOP,
		BOTTOM,
		FRONT,
		BACK,
		RIGHT,
		LEFT,
	};

	Collision(CollisionFace face = UNDEFINED, Entity* entity = 0) : face(face), entity(entity) {}

	CollisionFace face;
	Entity* entity;
};