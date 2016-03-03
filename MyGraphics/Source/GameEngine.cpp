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

GameEngine::GameEngine() : active(true), fps(0), elapsedTime(0), nextUpdate(0), transition(0), queue(NULL), shouldTerminate(false), advance(false)
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

void GameEngine::ChangeState()
{
	if (queue)
	{
		if (!states.empty())
		{
			states.back()->Exit();
			states.pop_back();
		}

		states.push_back(queue);
		states.back()->Init();

		queue = NULL;
	}
}

float GameEngine::GetTransition()
{
	return 1 - transition;
}

void GameEngine::ChangeState(GameState* state)
{
	queue = state;
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
	{
		Terminate();
		return false;
	}
}

#include "Time.h"

void GameEngine::Update(float dt)
{
	if (dt > 0.1f)
		dt = 0.1f;

	if (queue)
	{
		Rise(transition, transitionRate * Time.GetUnscaledTime(), 1);

		if (transition == 1)
			advance = true;
		
		if (advance)
		{
			ChangeState();
			Application::Instance().ResetTimer();

			advance = false;
		}
	}
	else if (!states.empty())
	{
		Fall(transition, transitionRate *  Time.GetUnscaledTime(), 0);

		states.back()->Update(dt);
	}

	if (elapsedTime > nextUpdate)
	{
		fps = 1.0f / dt;
		nextUpdate += 0.1f;
	}

	elapsedTime += dt;
}

#include "FBO.h"
#include "Screen.h"
#include "Mesh2D.h"

void GameEngine::Render()
{
	if (!states.empty())
	{
		states.back()->Render();
	}

	FBO::Unbind();
	Graphics.font->ImmediateDraw(ToString((int)fps), Screen.GetProjectionWidth() - 32, 0, 48);

	if (shouldTerminate)
	{
		while (!states.empty())
			PopState();

		active = false;
	}
}

void GameEngine::Terminate()
{
	shouldTerminate = true;
}