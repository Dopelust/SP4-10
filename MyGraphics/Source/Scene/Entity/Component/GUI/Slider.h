#pragma once

#include "../Component.h"

class TextRenderer2D;
class Transform;
class Button;
class Slider : public Component
{
public:
	enum SliderType
	{
		SLIDER_HORIZONTAL,
		SLIDER_VERTICAL,
	};

	enum SliderValue
	{
		SLIDER_INTEGER,
		SLIDER_FLOAT,
	};

	Button* guide;
	Transform* fill;

	SliderType type;
	SliderValue valueType;

	Slider();
	~Slider();

	void Init(Entity* ent);
	void Update(double dt);

	void SetValue(float value);

	bool ValueChanged();
	float GetValue();

	void SetMin(float min);
	void SetMax(float max);

	void SetText(TextRenderer2D* text);

private:
	TextRenderer2D* text;
	Button* button;
	Transform* transform;

	void SetPosition(const Vector2& position);
	bool click;

	float value, min, max;
	float prev;
};