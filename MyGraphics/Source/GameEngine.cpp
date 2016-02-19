#include <iostream>
using namespace std;

#include "Application.h"
#include "Utility.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "GameState.h"
#include "InputHandler.h"

GameEngine& GameEngine::Instance()
{
	static GameEngine engine;
	return engine;
}

bool GameEngine::IsActive()
{
	return active;
}

GameEngine::GameEngine() : active(true), fps(0), elapsedTime(0), nextUpdate(0)
{
}

GameEngine::~GameEngine()
{
	while (!states.empty())
	{
		states.back()->Exit();
		states.pop_back();
	}
}

void GameEngine::ChangeState(GameState* state)
{
	if (!states.empty())
	{
		states.back()->Exit();
		states.pop_back();
	}

	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PushState(GameState* state)
{
	if (!states.empty())
	{
		states.back()->Pause();
	}

	states.push_back(state);
	states.back()->Init();
}

bool GameEngine::PopState()
{
	if (!states.empty())
	{
		states.back()->Exit();
		states.pop_back();
	}

	if (!states.empty())
	{
		states.back()->Resume();
		return true;
	}
	else
		return false;
}

void GameEngine::Update(float dt)
{
	if (!states.empty())
		states.back()->Update(dt);

	if (elapsedTime > nextUpdate)
	{
		fps = 1.0f / dt;
		nextUpdate+=0.5f;
	}

	elapsedTime += dt;
}

#include "FBO.h"
void GameEngine::Render()
{
	if (!states.empty())
		states.back()->Render();

	FBO::Unbind();
	Graphics.font->ImmediateDraw("fps: " + ToString((int)fps), 0, 0, 64);
}

void GameEngine::Terminate()
{
	while (!states.empty())
		PopState();

	active = false;
}

void GameEngine::HandleEvents()
{
	if (!states.empty())
		states.back()->HandleEvents();

	if (Input.IsPress(GLFW_KEY_ESCAPE))
	{
		PopState();

		if (states.empty())
			active = false;
	}
}