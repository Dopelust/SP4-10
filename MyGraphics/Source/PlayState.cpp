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
#include "Scene\Projectile\ProjectileDatabase.h"
#include "Scene\Enemy\EnemyDatabase.h"
#include "Scene\Stage\StageDatabase.h"

#include "Scene\Entity\Component\Physics\BoxCollider.h"
#include "Scene\Entity\Component\Script\TileSelector.h"
#include "Scene\Entity\Component\Script\TowerManager.h"
#include "Scene\Entity\Component\Script\TowerGUI.h"
#include "Scene\Entity\Component\TextRenderer2D.h"
#include "Scene\Entity\Component\Script\StageManager.h"
#include "Scene\Entity\Component\SpriteRenderer.h"
#include "Scene\Entity\Component\Script\PathFinder.h"
#include "Scene\Entity\Component\Script\EnemyController.h"

#include "Grid.h"
#include "Utility.h"
#include "Spritesheet.h"

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
	editor->AddComponent<BoxCollider>()->size.Set(TileWidth, TileHeight);
	editor->AddComponent<TowerManager>()->range = editor->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(), Resource.GetTexture("Range"), Vector4(1, 1, 1, 0.33f)));
	editor->AddComponent<TowerGUI>();

	Entity* selector = scene->root->AddChild("Selector");
	editor->GetComponent<TowerManager>()->selector = selector->AddComponent<TileSelector>();

	{
		entity = scene->canvas->AddChild("Hotbar");
		entity->transform->SetPosition(1100, 656);

		TowerDatabase::Init("archer");
		Entity* child = entity->AttachChild(EntityFactory::CreateButton(Vector2(0, 0), Vector2(48, 48), NULL, Vector3(0.9f, 0.9f, 0.9f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(64, 64), Resource.GetTexture("Archer"), Vector4(1,1,1,1)));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Archer", 128));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -24), ToString('$', TowerDatabase::GetData("archer")[0].cost).c_str(), 200));
		editor->GetComponent<TowerGUI>()->AddButton("archer", child->GetComponent<Button>());

		TowerDatabase::Init("fountain");
		child = entity->AttachChild(EntityFactory::CreateButton(Vector2(0, -72), Vector2(48, 48), NULL, Vector3(0.9f, 0.9f, 0.9f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(48, 48), Resource.GetTexture("Fountain"), Vector4(1, 1, 1, 1)));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Fountain", 128));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -24), ToString('$', TowerDatabase::GetData("fountain")[0].cost).c_str(), 200));
		editor->GetComponent<TowerGUI>()->AddButton("fountain", child->GetComponent<Button>());

		TowerDatabase::Init("sniper");
		child = entity->AttachChild(EntityFactory::CreateButton(Vector2(0, -144), Vector2(48, 48), NULL, Vector3(0.9f, 0.9f, 0.9f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(96, 96), Resource.GetTexture("Sniper"), Vector4(1, 1, 1, 1)));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Sniper", 128));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -24), ToString('$', TowerDatabase::GetData("sniper")[0].cost).c_str(), 200));
		editor->GetComponent<TowerGUI>()->AddButton("sniper", child->GetComponent<Button>());

		TowerDatabase::Init("dispenser");
		child = entity->AttachChild(EntityFactory::CreateButton(Vector2(100, 0), Vector2(48, 48), NULL, Vector3(0.9f, 0.9f, 0.9f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(96, 96), Resource.GetTexture("Dispenser"), Vector4(1, 1, 1, 1)));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Dispenser", 128));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -24), ToString('$', TowerDatabase::GetData("dispenser")[0].cost).c_str(), 200));
		editor->GetComponent<TowerGUI>()->AddButton("dispenser", child->GetComponent<Button>());
	}

	{
		entity = scene->canvas->AddChild("Info");
		entity->transform->SetPosition(1050, 400);

		{
			Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(60, 12), "", 256, false));
			editor->GetComponent<TowerGUI>()->name = child->GetComponent<TextRenderer2D>();
		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateSprite(Vector2(0, -8), Vector2(48, 48), Resource.GetSpritesheet("Rank")->GetSprite(0), Vector4(1,1,1)));
			child->GetComponent<SpriteRenderer>()->SetAlignCenter(false);
			child->GetComponent<SpriteRenderer>()->SetActive(false);

			editor->GetComponent<TowerGUI>()->rank = child->GetComponent<SpriteRenderer>();
		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -32), "Damage:", 150, false));
			child->GetComponent<TextRenderer2D>()->SetColor(1, 0, 0);

			child = child->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, 0), "", 150, false));
			child->GetComponent<TextRenderer2D>()->SetColor(1, 0, 0);

			editor->GetComponent<TowerGUI>()->damage = child->GetComponent<TextRenderer2D>();
 		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -64), "Range:", 150, false));
			child->GetComponent<TextRenderer2D>()->SetColor(0.25f, 0.25f, 1);

			child = child->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, 0), "", 150, false));
			child->GetComponent<TextRenderer2D>()->SetColor(0.25f, 0.25f, 1);

			editor->GetComponent<TowerGUI>()->range = child->GetComponent<TextRenderer2D>();
		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -96), "Speed:", 150, false));
			child = child->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, 0), "", 150, false));

			//editor->GetComponent<TowerGUI>()->cost = child->GetComponent<TextRenderer2D>();
		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateButton(Vector2(64, -150), Vector2(96, 32), NULL, Vector3(0, 0.8f, 0)));
			child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, 0), "Upgrade", 150));

			editor->GetComponent<TowerGUI>()->upgrade = child->GetComponent<Button>();

			child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, -150), "", 150, false));
			child->GetComponent<TextRenderer2D>()->SetColor(1, 1, 0);
			editor->GetComponent<TowerGUI>()->cost = child->GetComponent<TextRenderer2D>();
		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateButton(Vector2(64, -200), Vector2(96, 32), NULL, Vector3(0.8f, 0, 0)));
			child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, 0), "Sell", 150));

			editor->GetComponent<TowerGUI>()->sell = child->GetComponent<Button>();
			editor->GetComponent<TowerGUI>()->sell->Disable();

			child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, -200), "", 150, false));
			child->GetComponent<TextRenderer2D>()->SetColor(1, 1, 0);

			editor->GetComponent<TowerGUI>()->sellprice = child->GetComponent<TextRenderer2D>();
		}
	}

	editor->GetComponent<TowerManager>()->gui = editor->GetComponent<TowerGUI>();
	editor->GetComponent<TowerGUI>()->DisableUpgrades();

	//ProjectileDatabase::Init("arrow");
	EnemyDatabase::Init("jelly");
	StageDatabase::Init("level1");

	Entity* stageManager;
	stageManager = new Entity();
	stageManager->Rename("Stage Manager");
	vector<int> a;
	a.push_back(1);
	a.push_back(2);
	stageManager->AddComponent<PathFinder>();
	stageManager->AddComponent<StageManager>()->LateInit(scene->grid, a);
	stageManager->GetComponent<StageManager>()->LoadStage("level1");

	EnemyController::stage = stageManager->GetComponent<StageManager>();

	scene->root->AttachChild(stageManager);
	editor->GetComponent<TowerManager>()->stage = stageManager->GetComponent<StageManager>();

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

	TowerDatabase::Exit();
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