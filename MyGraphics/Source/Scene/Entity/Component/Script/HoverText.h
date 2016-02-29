#pragma once

#include "../Component.h"
#include "Vector3.h"

class Transform;
class Graphic2D;
class TextRenderer2D;

class HoverText : public Component
{
public:
	HoverText();
	~HoverText();

	Entity* owner;
	Entity* text;

	void Init(Entity* ent);
	void Update(double dt);

	void SetText(const char* text);

private:
	Transform* transform;
	Graphic2D* graphic;

	Vector3 offset;
};