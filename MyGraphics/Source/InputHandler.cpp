#include "InputHandler.h"
#include "Screen.h"
#include "GLFW\glfw3.h"

InputHandler& InputHandler::Instance()
{
	static InputHandler input;
	return input;
}

void InputHandler::ResetCursorPos()
{
	glfwSetCursorPos(Screen.window, Screen.width * 0.5f, Screen.height * 0.5f);
}

void InputHandler::ShowCursor(bool freezeCursor)
{
	glfwSetInputMode(Screen.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	this->freezeCursor = freezeCursor;
}

void InputHandler::HideCursor(bool freezeCursor)
{
	glfwSetInputMode(Screen.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->freezeCursor = freezeCursor;

	ResetCursorPos();
}

InputHandler::InputHandler() : pause(false), freezeCursor(true)
{
	for (int i = 0; i < 3; ++i)
		clickBuffer[i] = false;
}

InputHandler::~InputHandler()
{
}

string InputHandler::ProcessInput()
{
	string s;

	//SPACE
	if (IsPressOrRepeat(GLFW_KEY_SPACE))
		s += " ";

	//0-9
	for (int i = 48; i < 58; ++i)
	{
		if (IsPressOrRepeat(i))
			s += i;
	}

	//A-Z
	for (int i = 65; i < 91; ++i)
	{
		if (IsPressOrRepeat(i))
		{
			if (IsHeld(GLFW_KEY_LEFT_SHIFT) || IsHeld(GLFW_KEY_RIGHT_SHIFT))
				s += i;
			else
				s += i + 32;
		}
	}
	return s;
}
void InputHandler::Halt()
{
	pause = true;
}
void InputHandler::Resume()
{
	pause = false;
}

void InputHandler::Flush()
{
	for (int i = 32; i < GLFW_KEY_LAST + 1; ++i)
		key[i].state = -1;

	if (freezeCursor)
		ResetCursorPos();

	for (int i = 0; i < 3; ++i)
	{
		if (glfwGetMouseButton(Screen.window, i) != GLFW_PRESS)
			clickBuffer[i] = false;
		else
			clickBuffer[i] = true;
	}

	scrollX = scrollY = 0;
}

void InputHandler::SetKey(int key, int state)
{
	this->key[key].state = state;
	
	if (state == GLFW_RELEASE)
	{
		this->key[key].isPressed = false;
		this->key[key].releaseBuffer = false;
	}
	else
		this->key[key].isPressed = true;
}

void InputHandler::ApplyReleaseBuffer(int key)
{
	this->key[key].releaseBuffer = true;
}

bool InputHandler::IsState(int key, int state)
{
	return this->key[key].state == state;
}

bool InputHandler::IsPressOrRepeat(int key)
{
	return !this->key[key].releaseBuffer && (this->key[key].state == GLFW_PRESS || this->key[key].state == GLFW_REPEAT);
}

bool InputHandler::IsPress(int key)
{
	return this->key[key].state == GLFW_PRESS && !this->key[key].releaseBuffer && !pause;
}

bool InputHandler::IsHeld(int key)
{
	return this->key[key].isPressed && !pause;
}

bool InputHandler::IsMouseRelease(unsigned short button)
{
	return glfwGetMouseButton(Screen.window, button) == GLFW_RELEASE;
}

bool InputHandler::IsMouseHeld(unsigned short button)
{
	return glfwGetMouseButton(Screen.window, button) == GLFW_PRESS;
}

bool InputHandler::IsMousePress(unsigned short button)
{
	return glfwGetMouseButton(Screen.window, button) == GLFW_PRESS && !clickBuffer[button];
}

void InputHandler::ApplyMouseBuffer(unsigned short button)
{
	clickBuffer[button] = true;
}

void InputHandler::MouseRelease(unsigned short button)
{
	clickBuffer[button] = false;
}

void InputHandler::SetScroll(float x, float y)
{
	scrollX = x;
	scrollY = y;
}

#include "Vector2.h"

Vector2 InputHandler::GetScroll()
{
	return Vector2(scrollX, scrollY);
}

Vector2 InputHandler::GetCursorPos()
{
	double x, y;
	glfwGetCursorPos(Screen.window, &x, &y);

	return Vector2(x, Screen.height - y) * Vector2((float)Screen.GetProjectionWidth() / Screen.width, (float)Screen.GetProjectionHeight() / Screen.height);
}

void InputHandler::GetCursorOffset(double * xpos, double * ypos)
{
	glfwGetCursorPos(Screen.window, xpos, ypos);

	if (!pause)
	{
		*xpos = (int)(Screen.width * 0.5f - *xpos);
		*ypos = (int)(Screen.height * 0.5f - *ypos);
	}
	else
	{
		*xpos = 0;
		*ypos = 0;
	}
}
