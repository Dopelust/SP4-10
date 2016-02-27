#include "Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "InputHandler.h"
#include "MyMath.h"
#include "SoundEngine.h"

#include "Screen.h"

#include <fstream>

const unsigned char FPS = 60; // FPS of this game	
const unsigned int frameTime = 1000 / FPS; // time for each frame

Application& Application::Instance()
{
	static Application app;
	return app;
}

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
}

void scroll_callback(GLFWwindow* window, double x, double y)
{
	Input.SetScroll(x, y);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input.SetKey(key, action);
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	Screen.SetResolution(w, h);
	Graphics.Resize(w, h);
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	glfwSetErrorCallback(error_callback);
	
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	Screen.Init();

	glfwSetWindowSizeCallback(Screen.window, resize_callback);
	glfwSetMouseButtonCallback(Screen.window, mouse_callback);
	glfwSetScrollCallback(Screen.window, scroll_callback);
	glfwSetKeyCallback(Screen.window, key_callback);
	glewExperimental = true;
	
	GLenum err = glewInit();
	if (err != GLEW_OK)
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

	Math::InitRNG();

	Audio.Init();
	Graphics.Init(Screen.width, Screen.height);
}

#include "MenuState.h"
#include "TestState.h"

void Application::Run()
{
	Engine.PushState(&MenuState::Instance());
	Input.Flush();

	timer.startTimer();
	while (Engine.IsActive())
	{
		Engine.Update(timer.getElapsedTime());
		Engine.Render();

		Input.Flush();
		
		glfwSwapBuffers(Screen.window);
		glfwPollEvents();

		timer.waitUntil(frameTime);
	}
}

#include "LUAEngine.h"

void Application::Exit()
{
	Graphics.Exit();

	glfwDestroyWindow(Screen.window);
	glfwTerminate();

	LUA.Save("Data//properties.lua");
}

void Application::ResetTimer()
{
	timer.getElapsedTime();
}
