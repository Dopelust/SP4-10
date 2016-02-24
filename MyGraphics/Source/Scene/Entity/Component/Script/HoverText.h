#pragma once

#include "../Component.h"

class Transform;
class Graphic2D;
class TextRenderer2D;

class HoverText : public Component
{
public:
	HoverText();
	~HoverText();

	TextRenderer2D* text;

	void Init(Entity* ent);
	void Update(double dt);

	void SetText(const char* text);

private:
	Transform* transform;
	Graphic2D* graphic;
};