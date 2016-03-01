#include "Button.h"
#include "../../Entity.h"
#include "../Transform.h"
#include "../Graphic2D.h"

#include "../../../../InputHandler.h"
#include "Vector2.h"

Vector3 Button::GetMaxCoord()
{
	return transform->GetPosition() + transform->GetSize() * 0.5f;
}

Vector3 Button::GetMinCoord()
{
	return transform->GetPosition() - transform->GetSize() * 0.5f;
}

Vector4 Button::GetDisabledColor()
{
	Vector4 color = this->color;

	color.x *= 0.5f;
	color.y *= 0.5f;
	color.z *= 0.5f;

	return color;
}

Vector4 Button::GetHoverColor()
{
	Vector4 color = this->color;

	color.x *= 1.25f;
	color.y *= 1.25f;
	color.z *= 1.25f;

	return color;
}

Vector4 Button::GetClickColor()
{
	Vector4 color = this->color;

	color.x *= 0.75f;
	color.y *= 0.75f;
	color.z *= 0.75f;

	return color;
}

#include "../../../Scene.h"
#include "Canvas.h"

bool Button::IsHover()
{
	Vector2& cursor = Input.GetCursorPos();

	Vector3& min = GetMinCoord();
	Vector3& max = GetMaxCoord();
	
	if (cursor.x > min.x && cursor.x < max.x && cursor.y > min.y && cursor.y < max.y)
	{
		Canvas.SetFocus(this);
		return true;
	}

	return false;
}

Button::Button() : state(ButtonState::STATE_NULL), enabled(true), key(0)
{
}

bool Button::IsState(ButtonState state)
{
	return this->state == state;
}

void Button::Init(Entity * ent)
{
	transform = ent->GetComponent<Transform>();
	SetGraphic(ent->GetComponent<Graphic2D>());
}

#include "Utility.h"
void Button::Update(double dt)
{
	if (enabled)
		UpdateState();
	else
		state = STATE_NULL;
}

#include "../../../../SoundEngine.h"

void Button::UpdateState()
{
	switch (state)
	{
	case STATE_NULL:

		graphic->color = color;

		if (key && Input.IsPress(key))
		{
			Audio.Play2D("click");
			state = STATE_PRESS;
		}
		else if (IsHover() && !Input.IsMouseHeld(0))
		{
			Audio.Play2D("hover", 0.2f);
			state = STATE_HOVER;
		}

		break;
	case STATE_HOVER:

		graphic->color = GetHoverColor();

		if (key && Input.IsPress(key))
		{
			Audio.Play2D("click");
			state = STATE_PRESS;
		}
		else
		{
			if (!IsHover())
				state = STATE_NULL;
			if (Input.IsMousePress(0))
			{
				Audio.Play2D("click");
				state = STATE_CLICK;
			}
		}

		break;
	case STATE_PRIMED:

		graphic->color = color;

		if (key && Input.IsPress(key))
		{
			Audio.Play2D("click");
			state = STATE_PRESS;
		}
		else
		{
			if (IsHover())
				state = STATE_CLICK;
			else if (Input.IsMouseRelease(0))
				state = STATE_NULL;
		}

		break;
	case STATE_CLICK:

		graphic->color = GetClickColor();

		if (IsHover())
		{
			if (Input.IsMouseRelease(0))
				state = STATE_RELEASE;
		}
		else
			state = STATE_PRIMED;

		break;
	case STATE_RELEASE:

		graphic->color = color;

		if (IsHover())
			state = STATE_HOVER;
		else
			state = STATE_NULL;

		break;

	case STATE_PRESS:
		graphic->color = GetClickColor();

		if (!Input.IsHeld(key))
			state = STATE_RELEASE;

		break;
	}
}

void Button::SetKey(int key)
{
	this->key = key;
}

void Button::SetGraphic(Graphic2D * graphic)
{
	this->graphic = graphic;

	if (graphic)
		color = graphic->color;
}


void Button::SetColor(float r, float g, float b, float a)
{
	if (graphic)
		color = graphic->color = Vector4(r, g, b, a);
}


bool Button::IsEnabled()
{
	return enabled;
}

void Button::Enable()
{
	enabled = true;

	graphic->color = color;
}

void Button::Disable()
{
	enabled = false;

	graphic->color = GetDisabledColor();
}
