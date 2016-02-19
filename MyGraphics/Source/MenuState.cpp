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

#include "Scene\Entity\Component\GUI\Button.h"

#include "Screen.h"
void MenuState::Init()
{
	glClearColor(0.2, 0.2, 0.2, 1);

	scene = new Scene(NULL);

	Entity* entity = EntityFactory::GenerateButton(Vector2(scene->GetResolutionX(scene->canvas) * 0.5f, 400), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "LEVEL EDITOR", 128));
	editor = entity->GetComponent<Button>();

	entity = EntityFactory::GenerateButton(Vector2(scene->GetResolutionX(scene->canvas) * 0.5f, 500), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "PLAY", 128));
	play = entity->GetComponent<Button>();

	entity = EntityFactory::GenerateButton(Vector2(scene->GetResolutionX(scene->canvas) * 0.5f, 300), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "OPTIONS", 128));

	entity = EntityFactory::GenerateButton(Vector2(scene->GetResolutionX(scene->canvas) * 0.5f, 200), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "QUIT", 128));
	exit = entity->GetComponent<Button>();

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

#include "TestState.h"
#include "PlayState.h"

void MenuState::HandleEvents()
{
	if (play->IsState())
		Engine.ChangeState(&PlayState::Instance());

	if (editor->IsState())
		Engine.ChangeState(&TestState::Instance());

	if (exit->IsState())
		Engine.Terminate();
}

#include "FontManager.h"

void MenuState::Render()
{
	Graphics.Start();

	Graphics.ForwardPass(0);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	scene->DrawWorld();
	Graphics.Render2D("2D", scene->GetResolutionX(scene->root), scene->GetResolutionY(scene->root), false);

	scene->DrawCanvas();
	Graphics.Render2D("2D", scene->GetResolutionX(scene->canvas), scene->GetResolutionY(scene->canvas), true);

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