#pragma once

#include "../Component.h"
#include "Vector4.h"

class Transform;
class Graphic2D;
class TextRenderer2D;

class Button : public Component
{
public:
	Button();

	enum ButtonState
	{
		STATE_NULL,
		STATE_HOVER,
		STATE_PRIMED,
		STATE_CLICK,
		STATE_PRESS,
		STATE_RELEASE,
	};

	TextRenderer2D* text;

	Vector3 GetMaxCoord();
	Vector3 GetMinCoord();
	bool IsHover();

	bool IsState(ButtonState state = STATE_RELEASE);

	void Init(Entity* ent);
	void Update(double dt);
	void UpdateState();

	void SetGraphic(Graphic2D* graphic);

	Transform* transform;

	bool IsEnabled();
	void Enable();
	void Disable();

	void SetColor(float r, float g, float b, float a);
	void SetKey(int key);

private:
	int key;

	bool enabled;
	ButtonState state;

	Graphic2D* graphic;
	Vector4 color;

	Vector4 GetDisabledColor();
	Vector4 GetHoverColor();
	Vector4 GetClickColor();
};