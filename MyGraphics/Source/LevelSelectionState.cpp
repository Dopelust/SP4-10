#include "LevelSelectionState.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "Assets.h"

#include "InputHandler.h"

#include <iostream>
using namespace::std;

LevelSelectionState& LevelSelectionState::Instance()
{
	static LevelSelectionState state;
	return state;
}

LevelSelectionState::LevelSelectionState()
{
}

LevelSelectionState::~LevelSelectionState()
{
}

#include "Scene\Scene.h"
#include "Scene\Entity\Entity.h"
#include "Scene\Entity\EntityFactory.h"

#include "Scene\Entity\Component\GUI\Button.h"

#include "Screen.h"
void LevelSelectionState::Init()
{
	glClearColor(0.2, 0.2, 0.2, 1);

	scene = new Scene(NULL);

	Entity* entity = EntityFactory::GenerateButton(Vector2(scene->GetResolutionX(scene->canvas) * 0.33f, 500), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Level 1", 128));
	level1 = entity->GetComponent<Button>();

	entity = EntityFactory::GenerateButton(Vector2(scene->GetResolutionX(scene->canvas) * 0.66f, 500), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Level 2", 128));
	level2 = entity->GetComponent<Button>();

	entity = EntityFactory::GenerateButton(Vector2(scene->GetResolutionX(scene->canvas) * 0.33f, 300), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Level 3", 128));
	level3 = entity->GetComponent<Button>();

	entity = EntityFactory::GenerateButton(Vector2(scene->GetResolutionX(scene->canvas) * 0.66f, 300), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Level 4", 128));
	level4 = entity->GetComponent<Button>();

	entity = EntityFactory::GenerateButton(Vector2(scene->GetResolutionX(scene->canvas) * 0.5f, 200), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Custom Level", 128));
	custom = entity->GetComponent<Button>();

	entity = EntityFactory::GenerateButton(Vector2(scene->GetResolutionX(scene->canvas) * 0.5f, 100), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Return", 128));
	Return = entity->GetComponent<Button>();

	entity = scene->root->AttachChild(EntityFactory::CreateGraphic(Vector2(scene->GetResolutionX(scene->canvas) * 0.5f, scene->GetResolutionY(scene->canvas) * 0.5f), Vector2(scene->GetResolutionX(scene->canvas), scene->GetResolutionY(scene->canvas)), Resource.GetTexture("NightChanges"), Vector4(1, 1, 1, 1.0f)));

	Resume();
}

void LevelSelectionState::Exit()
{
	if (scene)
	{
		scene->Exit();

		delete scene;
		scene = NULL;
	}
}

void LevelSelectionState::Update(float dt)
{
	scene->Update(dt);
}

#include "TestState.h"
#include "PlayState.h"
#include "MenuState.h"

void LevelSelectionState::HandleEvents()
{
	if (level1->IsState())
		Engine.ChangeState(&PlayState::Instance());

	if (level2->IsState())
		Engine.ChangeState(&PlayState::Instance());

	if (level3->IsState())
		Engine.ChangeState(&PlayState::Instance());

	if (level4->IsState())
		Engine.ChangeState(&PlayState::Instance());

	if (custom->IsState())
		Engine.ChangeState(&TestState::Instance());

	if (Return->IsState())
		Engine.ChangeState(&MenuState::Instance());
}

#include "FontManager.h"

void LevelSelectionState::Render()
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

void LevelSelectionState::Pause()
{
}

void LevelSelectionState::Resume()
{
	Input.ShowCursor();
	Scene::scene = scene;
}