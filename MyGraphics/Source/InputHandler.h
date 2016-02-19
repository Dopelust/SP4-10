#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "GLFW\glfw3.h"

#define Input InputHandler::Instance()

struct Vector2;

struct Key
{
	bool releaseBuffer{ false };
	int state{ -1 };
	bool isPressed{ false };
};

#include <string>
using namespace::std;

class InputHandler
{
public:
	static InputHandler& Instance();

	string ProcessInput();
	void Halt();
	void Resume();
	void Flush();

	void SetKey(int key, int state);
	void ApplyReleaseBuffer(int key);

	bool IsState(int key, int state);
	bool IsPressOrRepeat(int key);
	bool IsPress(int key);
	bool IsHeld(int key);

	bool IsMouseRelease(unsigned short button);
	bool IsMouseHeld(unsigned short button);
	bool IsMousePress(unsigned short button);
	void ApplyMouseBuffer(unsigned short button);
	void MouseRelease(unsigned short button);

	void SetScroll(float x, float y);
	Vector2 GetScroll();

	Vector2 GetCursorPos();
	void GetCursorOffset(double *xpos, double *ypos);

	void ResetCursorPos();

	void ShowCursor(bool freezeCursor = false);
	void HideCursor(bool freezeCursor = true);
	
private:
	InputHandler();
	~InputHandler();

	bool pause;
	Key key[GLFW_KEY_LAST + 1];
	float scrollX, scrollY;

	bool freezeCursor;
	bool clickBuffer[3];
};

#endif