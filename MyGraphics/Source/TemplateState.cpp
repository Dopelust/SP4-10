#include "PlayState.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "Assets.h"

#include "InputHandler.h"

#include <iostream>
using namespace::std;

PlayState& PlayState::Instance()
{
	static PlayState state;
	return state;
}

PlayState::PlayState()
{
}

PlayState::~PlayState()
{
}

#include "Scene\Scene.h"
#include "Scene\Entity\Entity.h"
#include "Scene\Entity\EntityFactory.h"
#include "Scene\Entity\Component\GUI\Button.h"

void PlayState::Init()
{
	glClearColor(0.2, 0.2, 0.2, 1);

	scene = new Scene(NULL);

	Entity* entity = EntityFactory::GenerateButton(Vector2(200, 200), Vector2(200, 100), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Return", 128));
	menu = entity->GetComponent<Button>();

	Resume();
}

void PlayState::Exit()
{
	if (scene)
	{
		scene->Exit();

		delete scene;
		scene = NULL;
	}
}

void PlayState::Update(float dt)
{
	scene->Update(dt);
}

#include "MenuState.h"

void PlayState::HandleEvents()
{
	if (menu->IsState())
		Engine.ChangeState(&MenuState::Instance());
}

void PlayState::Render()
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

void PlayState::Pause()
{
}

void PlayState::Resume()
{
	Input.ShowCursor();
	Scene::scene = scene; 
}