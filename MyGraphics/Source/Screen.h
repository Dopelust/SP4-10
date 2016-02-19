#pragma once

#define Screen Window::Instance()

struct GLFWwindow;
class Window
{
public:
	static Window& Instance();

	void Init();

	GLFWwindow* window;
	int width;
	int height;
	
	float GetAspectRatio();
	void SetResolution(int width, int height);

	void SetProjectionResolution(int width, int height);
	int GetProjectionWidth();
	int GetProjectionHeight();

private:
	float aspect;

	int pwidth, pheight;
};