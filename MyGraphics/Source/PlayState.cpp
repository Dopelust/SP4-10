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

PlayState::PlayState() : bgm(NULL)
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
#include "Scene\Entity\Component\Script\StageGUI.h"
#include "Scene\Entity\Component\SpriteRenderer.h"
#include "Scene\Entity\Component\Script\PathFinder.h"
#include "Scene\Entity\Component\Script\EnemyController.h"
#include "Scene\Entity\Component\Script\HoverText.h"

#include "Grid.h"
#include "Utility.h"
#include "Spritesheet.h"
#include "FileSystem.h"
#include "SoundEngine.h"

void PlayState::Init()
{
	glClearColor(0.2, 0.2, 0.2, 1);

	if (!Audio.IsPlaying(Audio.GetSoundPack("bgm")))
		bgm = Audio.Play2D(Audio.GetSoundPack("bgm"), 1);

	scene = new Scene(NULL);
	scene->camera.position.Set(0, -TileHeight, 0);

	Entity* entity = EntityFactory::GenerateButton(Vector2(1200, 50), Vector2(80, 30), NULL, Vector3(0.5f, 0.5f, 0.5f));
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
		entity->transform->SetPosition(1090, 640);

		TowerDatabase::Init("bubble_blower");
		Entity* child = entity->AttachChild(EntityFactory::CreateButton(Vector2(0, 0), Vector2(48, 48), NULL, Vector3(0.9f, 0.9f, 0.9f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(42, 42), NULL, Vector4(0, 0, 0)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(0, 10.5f), Vector2(42, 21), NULL, Vector4(1, 1, 1, 0.33f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(64, 64), Resource.GetTexture("Bubble Blower"), Vector4(1,1,1,1)));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -24), ToString('$', TowerDatabase::GetData("bubble_blower")[0].cost).c_str(), 200));
		editor->GetComponent<TowerGUI>()->AddButton("bubble_blower", child->GetComponent<Button>());

		TowerDatabase::Init("fountain");
		child = entity->AttachChild(EntityFactory::CreateButton(Vector2(0, -72), Vector2(48, 48), NULL, Vector3(0.9f, 0.9f, 0.9f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(42, 42), NULL, Vector4(0, 0, 0)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(0, 10.5f), Vector2(42, 21), NULL, Vector4(1, 1, 1, 0.33f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(48, 48), Resource.GetTexture("Fountain"), Vector4(1, 1, 1, 1)));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -24), ToString('$', TowerDatabase::GetData("fountain")[0].cost).c_str(), 200));
		editor->GetComponent<TowerGUI>()->AddButton("fountain", child->GetComponent<Button>());

		TowerDatabase::Init("sniper");
		child = entity->AttachChild(EntityFactory::CreateButton(Vector2(0, -144), Vector2(48, 48), NULL, Vector3(0.9f, 0.9f, 0.9f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(42, 42), NULL, Vector4(0, 0, 0)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(0, 10.5f), Vector2(42, 21), NULL, Vector4(1, 1, 1, 0.33f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(96, 96), Resource.GetTexture("Sniper"), Vector4(1, 1, 1, 1)));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -24), ToString('$', TowerDatabase::GetData("sniper")[0].cost).c_str(), 200));
		editor->GetComponent<TowerGUI>()->AddButton("sniper", child->GetComponent<Button>());

		TowerDatabase::Init("dispenser");
		child = entity->AttachChild(EntityFactory::CreateButton(Vector2(100, 0), Vector2(48, 48), NULL, Vector3(0.9f, 0.9f, 0.9f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(42, 42), NULL, Vector4(0, 0, 0)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(0, 10.5f), Vector2(42, 21), NULL, Vector4(1, 1, 1, 0.33f)));
		child->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(80, 80), Resource.GetTexture("Dispenser"), Vector4(1, 1, 1, 1)));
		child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -24), ToString('$', TowerDatabase::GetData("dispenser")[0].cost).c_str(), 200));
		editor->GetComponent<TowerGUI>()->AddButton("dispenser", child->GetComponent<Button>());
	}

	{
		entity = scene->canvas->AddChild("Info");
		entity->transform->SetPosition(1030, 400);

		{
			Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(60, 12), "", 200, false));
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
			child->GetComponent<TextRenderer2D>()->color.Set(1, 0, 0);

			child = child->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, 0), "", 150, false));
			child->GetComponent<TextRenderer2D>()->color.Set(1, 0, 0);

			editor->GetComponent<TowerGUI>()->damage = child->GetComponent<TextRenderer2D>();
 		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -64), "Range:", 150, false));
			child->GetComponent<TextRenderer2D>()->color.Set(0.1f, 0.1f, 1);

			child = child->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, 0), "", 150, false));
			child->GetComponent<TextRenderer2D>()->color.Set(0.1f, 0.1f, 1);

			editor->GetComponent<TowerGUI>()->range = child->GetComponent<TextRenderer2D>();
		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -96), "Force:", 150, false));
			child->GetComponent<TextRenderer2D>()->color.Set(0, 1, 0);

			child = child->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, 0), "", 150, false));
			child->GetComponent<TextRenderer2D>()->color.Set(0, 1, 0);

			editor->GetComponent<TowerGUI>()->force = child->GetComponent<TextRenderer2D>();
		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -128), "Speed:", 150, false));
			child->GetComponent<TextRenderer2D>()->color.Set(1, 0, 1);

			child = child->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, 0), "", 150, false));
			child->GetComponent<TextRenderer2D>()->color.Set(1, 0, 1);

			editor->GetComponent<TowerGUI>()->speed = child->GetComponent<TextRenderer2D>();
		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, -160), "Projectiles:", 150, false));
			child = child->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, 0), "", 150, false));

			editor->GetComponent<TowerGUI>()->projectiles = child->GetComponent<TextRenderer2D>();
		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateButton(Vector2(64, -230), Vector2(96, 32), NULL, Vector3(0, 0.8f, 0)));
			child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, 0), "Upgrade", 150));

			editor->GetComponent<TowerGUI>()->upgrade = child->GetComponent<Button>();

			child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, -230), "", 150, false));
			child->GetComponent<TextRenderer2D>()->color.Set(1, 1, 0);
			editor->GetComponent<TowerGUI>()->cost = child->GetComponent<TextRenderer2D>();
		}
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateButton(Vector2(64, -280), Vector2(96, 32), NULL, Vector3(0.8f, 0, 0)));
			child->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, 0), "Sell", 150));

			editor->GetComponent<TowerGUI>()->sell = child->GetComponent<Button>();
			editor->GetComponent<TowerGUI>()->sell->Disable();

			child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(150, -280), "", 150, false));
			child->GetComponent<TextRenderer2D>()->color.Set(1, 1, 0);

			editor->GetComponent<TowerGUI>()->sellprice = child->GetComponent<TextRenderer2D>();
		}
	}

	Entity* hover = EntityFactory::GenerateGraphic(Vector2(), Vector2(), NULL, Vector4(0, 0, 0, 0.75f), 1);
	hover->AddComponent<HoverText>()->text = hover->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "", 160, false));

	editor->GetComponent<TowerManager>()->gui = editor->GetComponent<TowerGUI>();
	editor->GetComponent<TowerGUI>()->DisableUpgrades();
	editor->GetComponent<TowerGUI>()->hover = hover->GetComponent<HoverText>();

	EnemyDatabase::Init("jelly");

	Entity* stageManager;
	stageManager = new Entity();
	stageManager->Rename("Stage Manager");
	stageManager->AddComponent<PathFinder>();
	stage = stageManager->AddComponent<StageManager>();
	stage->gui = stageManager->AddComponent<StageGUI>();

	if (stage->Load("Data//Save//stats.txt"))
	{
		scene->CreateSpatialPartition(Scene::GRID_3D_VOXEL);
		scene->grid->Load(ToString("Data//Levels//" + stage->GetStageName() + ".csv").c_str());
	}
	else
	{
		stage->LoadStage(level);

		scene->CreateSpatialPartition(Scene::GRID_3D_VOXEL);
		scene->grid->Load(ToString("Data//Levels//" + level + ".csv").c_str());
	}

	vector<int> a;
	a.push_back(1);
	a.push_back(2);
	stage->LateInit(scene->grid, a);

	EnemyController::stage = stageManager->GetComponent<StageManager>();

	scene->root->AttachChild(stageManager);
	editor->GetComponent<TowerManager>()->stage = stageManager->GetComponent<StageManager>();
	stageManager->GetComponent<StageManager>()->tower = editor->GetComponent<TowerManager>();

	tower = editor->GetComponent<TowerManager>();
	tower->Load("Data//Save//save.txt");

	Resume();
}

void PlayState::Exit()
{
	//stage->Save("Data//Save//stats.txt");
	//tower->Save("Data//Save//save.txt");

	if (scene)
	{
		scene->Exit();

		delete scene;
		scene = NULL;
	}

	TowerDatabase::Exit();

	if (bgm)
	{
		Audio.StopPlaying(bgm);
		bgm = NULL;
	}
}

#include "MenuState.h"

void PlayState::Update(float dt)
{
	if (bgm->isFinished())
			bgm = Audio.Play2D(Audio.GetSoundPack("bgm"), 1);

	scene->Update(dt);

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