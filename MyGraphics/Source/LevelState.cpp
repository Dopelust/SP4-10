#include "MenuState.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "Assets.h"

#include "InputHandler.h"

#include <iostream>
using namespace::std;

MenuState& MenuState::Instance()
{
	static MenuState state;
	return state;
}

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

#include "Scene\Scene.h"
#include "Scene\Entity\Entity.h"
#include "Scene\Entity\EntityFactory.h"

void MenuState::Init()
{
	glClearColor(0.2, 0.2, 0.2, 1);

	scene = new Scene(NULL);

	EntityFactory::GenerateButton(Vector2(200, 200), Vector2(200, 100), NULL, Vector3(0.5f, 0.5f, 0.5f))->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "LEVEL EDITOR", 128));

	Resume();
}

void MenuState::Exit()
{
	if (scene)
	{
		scene->Exit();

		delete scene;
		scene = NULL;
	}
}

void MenuState::Update(float dt)
{
	scene->Update(dt);
}

void MenuState::HandleEvents()
{
}

void MenuState::Render()
{
	Graphics.Start();

	Graphics.ForwardPass(0);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	scene->DrawWorld();
	Graphics.Render2D("2D", false);
	
	scene->DrawCanvas();
	Graphics.Render2D("2D", true);

	Graphics.ForwardPass(1);

	Graphics.Finish();
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
	Input.ShowCursor();
	Scene::scene = scene; 
}