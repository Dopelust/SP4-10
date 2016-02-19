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
#include "Scene\Entity\Component\Transform.h"
#include "Scene\Entity\EntityFactory.h"
#include "Scene\Entity\Component\GUI\Button.h"
#include "Scene\Tower\TowerDatabase.h"

#include "Scene\Entity\Component\Script\TileSelector.h"
#include "Scene\Entity\Component\Script\TowerPlacer.h"
#include "Scene\Entity\Component\Script\TowerPicker.h"
#include "Scene\Entity\Component\Script\TowerPlacerGUI.h"
#include "Scene\Entity\Component\Script\TowerInfoGUI.h"
#include "Scene\Entity\Component\TextRenderer2D.h"
#include "Scene\Entity\Component\Script\StageManager.h"

#include "Grid.h"
#include "Utility.h"

void PlayState::Init()
{
	glClearColor(0.2, 0.2, 0.2, 1);

	scene = new Scene(NULL);
	scene->CreateSpatialPartition(Scene::GRID_3D_VOXEL);
	scene->grid->Load("Data//Levels//level1.csv");

	Entity* entity = EntityFactory::GenerateButton(Vector2(1200, 50), Vector2(100, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Return", 128));
	menu = entity->GetComponent<Button>();

	Entity* editor = scene->root->AttachChild(EntityFactory::CreateGraphic(Vector2(TileWidth * 0.5f, TileHeight * 0.5f), Vector2(TileWidth, TileHeight), NULL, Vector4(1, 1, 1, 0.2f)));
	editor->AddComponent<TowerPlacer>()->range = editor->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(), Resource.GetTexture("Range"), Vector4(1, 1, 1, 0.33f)));
	editor->AddComponent<TowerPlacerGUI>();
	editor->AddComponent<TowerPicker>();

	Entity* selector = scene->root->AddChild("Selector");
	editor->GetComponent<TowerPlacer>()->selector = selector->AddComponent<TileSelector>();

	{
		entity = scene->canvas->AddChild("Hotbar");
		entity->transform->SetPosition(1200, 656);

		TowerDatabase::Init("archer");
		Entity* child = entity->AttachChild(EntityFactory::CreateButton(Vector2(0, 0), Vector2(48, 48), NULL, Vector3(0.9f, 0.9f, 0.9f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(64, 64), Resource.GetTexture("Archer"), Vector4(1,1,1,1)));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Archer", 128));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -24), ToString('$', TowerDatabase::GetData("archer")["INITIAL"].cost).c_str(), 200));
		editor->GetComponent<TowerPlacerGUI>()->AddButton("archer", child->GetComponent<Button>());

		TowerDatabase::Init("water");
		child = entity->AttachChild(EntityFactory::CreateButton(Vector2(0, -64), Vector2(48, 48), NULL, Vector3(0.9f, 0.9f, 0.9f)));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Water", 128));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -24), ToString('$', TowerDatabase::GetData("water")["INITIAL"].cost).c_str(), 200));
		editor->GetComponent<TowerPlacerGUI>()->AddButton("water", child->GetComponent<Button>());

		TowerDatabase::Init("sniper");
		child = entity->AttachChild(EntityFactory::CreateButton(Vector2(0, -128), Vector2(48, 48), NULL, Vector3(0.9f, 0.9f, 0.9f)));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Sniper", 128));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -24), ToString('$', TowerDatabase::GetData("sniper")["INITIAL"].cost).c_str(), 200));
		editor->GetComponent<TowerPlacerGUI>()->AddButton("sniper", child->GetComponent<Button>());
	}

	{
		entity = scene->canvas->AddChild("Info");
		entity->transform->SetPosition(1050, 350);
		entity->AddComponent<TowerInfoGUI>();

		{
			Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, 0), "Damage:", 150, false));
			child->GetComponent<TextRenderer2D>()->SetColor(1, 0, 0);

			child = child->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, 0), "", 150, false));
			child->GetComponent<TextRenderer2D>()->SetColor(1, 0, 0);

			entity->GetComponent<TowerInfoGUI>()->damage = child->GetComponent<TextRenderer2D>();
 		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -32), "Range:", 150, false));
			child->GetComponent<TextRenderer2D>()->SetColor(0.25f, 0.25f, 1);

			child = child->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, 0), "", 150, false));
			child->GetComponent<TextRenderer2D>()->SetColor(0.25f, 0.25f, 1);

			entity->GetComponent<TowerInfoGUI>()->range = child->GetComponent<TextRenderer2D>();
		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -64), "Speed:", 150, false));
			child = child->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, 0), "", 150, false));

			entity->GetComponent<TowerInfoGUI>()->cost = child->GetComponent<TextRenderer2D>();
		}
	}

	editor->GetComponent<TowerPlacer>()->info = entity->GetComponent<TowerInfoGUI>();

	Entity* stageManager;
	stageManager = new Entity();
	vector<int> a;
	a.push_back(1);
	a.push_back(2);
	stageManager->AddComponent<StageManager>()->LateInit("test", scene->grid, a);

	scene->root->AttachChild(stageManager);
	editor->GetComponent<TowerPlacer>()->stage = stageManager->GetComponent<StageManager>();

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
	Graphics.Render2D("2D", scene->GetResolutionX(scene->root), scene->GetResolutionY(scene->root), false);

	scene->DrawCanvas();
	Graphics.Render2D("2D", scene->GetResolutionX(scene->canvas), scene->GetResolutionY(scene->canvas), true);

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