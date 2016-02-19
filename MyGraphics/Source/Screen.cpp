#include "Screen.h"

float Window::GetAspectRatio()
{
	return aspect;
}

void Window::SetResolution(int width, int height)
{
	this->width = width;
	this->height = height;

	aspect = (float)width / (float)height;
}

void Window::SetProjectionResolution(int width, int height)
{
	pwidth = width;
	pheight = height;
}

int Window::GetProjectionWidth()
{
	return pwidth;
}

int Window::GetProjectionHeight()
{
	return pheight;
}

Window & Window::Instance()
{
	static Window window;
	return window;
}

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "LUAEngine.h"

void Window::Init()
{
	window = glfwCreateWindow(1920, 1080, "min", NULL, NULL);
	glfwSetWindowPos(window, 43, 8);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);	
	LUA.Load("Data//properties.lua");

	SetResolution(LUA.GetGlobalNumber("SCREEN_WIDTH"), LUA.GetGlobalNumber("SCREEN_HEIGHT"));
	glfwSetWindowSize(window, width, height);
}
