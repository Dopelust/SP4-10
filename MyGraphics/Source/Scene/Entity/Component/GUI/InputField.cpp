#include "InputField.h"
#include "../../Entity.h"
#include "../Transform.h"
#include "../TextRenderer2D.h"
#include "Button.h"

#include "../../../../InputHandler.h"

InputField::InputField() : focus(false), timer(0), limit(INT_MAX)
{
}
InputField::~InputField()
{
}

void InputField::SetTicker(Entity * ticker)
{
	this->ticker = ticker;
}

void InputField::SetLimit(int limit)
{
	this->limit = limit;
}

void InputField::SetTextRenderer(TextRenderer2D* renderer)
{
	this->renderer = renderer;
}

string InputField::GetOutput()
{
	return output;
}

void InputField::SetOutput(const char * output)
{
	this->output = output;
}

void InputField::SetActivator(Button* activator)
{
	this->activator = activator;
}

#include "../../../../FontManager.h"

void InputField::Init(Entity * ent)
{
	root = ent;
}

void InputField::Update(double dt)
{
	if (activator->IsState(Button::ButtonState::STATE_CLICK))
	{
		focus = true;
		timer = 0;

		Input.Halt();
	}
	else if (Input.IsMousePress(0))
	{
		focus = false;

		Input.Resume();
	}

	if (focus)
	{
		string in = Input.ProcessInput();

		if (output.size() < limit && in.size() > 0)
		{
			output += in;
			timer = 0;
		}
			
		if (Input.IsPressOrRepeat(GLFW_KEY_BACKSPACE) && output.size() > 0)
		{
			output.pop_back();
			timer = 0;
		}

		timer += dt;
		ticker->transform->Position().x = renderer->GetFont()->GetFont()->GetTextSize(output).x * root->transform->GetSize().x + root->transform->GetSize().x * 0.025f;
	}

	if (focus && (int)(timer * 2) % 2 == 0)
		ticker->SetActive(true);
	else
		ticker->SetActive(false);

	renderer->SetText(output.c_str());
}