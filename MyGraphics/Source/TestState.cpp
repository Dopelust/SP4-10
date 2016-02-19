#include "TestState.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "Assets.h"

#include "InputHandler.h"

#include <iostream>
using namespace::std;

TestState& TestState::Instance()
{
	static TestState state;
	return state;
}

TestState::TestState()
{
}

TestState::~TestState()
{
}

#include "Scene\Scene.h"
#include "Scene\Entity\Component\Graphic2D.h"
#include "Scene\Entity\Entity.h"
#include "Scene\Entity\EntityFactory.h"
#include "Scene\Entity\Component\Transform.h"
#include "Scene\Entity\Component\SpriteAnimator.h"
#include "Scene\Entity\Component\SpriteRenderer.h"

#include "FileSystem.h"
#include "Utility.h"
#include "LUAEngine.h"

#include "Grid.h"
#include "Cell.h"

#include "Scene\Entity\Component\Script\TileSelector.h"
#include "Scene\Entity\Component\Script\TileEditor.h"
#include "Scene\Entity\Component\Script\TileEditorGUI.h"

#include "Scene\Entity\Component\GUI\Button.h"

#include "Scene\Entity\Component\GUI\InputField.h"
#include "Spritesheet.h"

#include "Scene\Entity\Component\Script\WorldZoomScript.h"

void TestState::Init()
{
	glClearColor(0.2, 0.2, 0.2, 1);

	scene = new Scene("Data//Scene//Test");
	scene->CreateSpatialPartition(Scene::GRID_3D_VOXEL);

	scene->root->AddComponent<WorldZoomScript>();

	Entity* editor = scene->root->AttachChild(EntityFactory::CreateGraphic(Vector2(TileWidth * 0.5f, TileHeight * 0.5f), Vector2(TileWidth, TileHeight), NULL, Vector4(1, 1, 1, 0.5f)));
	editor->AddComponent<TileSelector>();
	editor->AddComponent<TileEditor>();
	editor->AddComponent<TileEditorGUI>();

	{
		Entity* entity = scene->canvas->AddChild("Hotbar");
		entity->transform->SetPosition(1200, 656);

		for (int i = 0; i < 5; ++i)
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateButton(Vector2(0, -64 * i), Vector2(48, 48), Resource.GetTexture("Tileset"), Vector3(1, 1, 1)));

			Vector4& uv = Resource.GetSpritesheet("Tileset")->GetSprite(i)->GetUV();
			child->GetComponent<Graphic2D>()->SetUV(uv.x, uv.y, uv.z, uv.w);

			editor->GetComponent<TileEditorGUI>()->AddButton(child->GetComponent<Button>());
		}

		editor->GetComponent<TileEditorGUI>()->select = entity->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(100, 100), Resource.GetTexture("Circle"), Vector4(1, 1, 1)));
	}

	Entity* entity = EntityFactory::GenerateButton(Vector2(1200, 50), Vector2(100, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Return", 128));
	menu = entity->GetComponent<Button>();

	entity = EntityFactory::GenerateInputField(Vector2(256, 680), Vector3(0, 0, 0), 16, 200);
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(-220, 0), "File:", 256, false));
	input = entity->GetChild("Input Field")->GetComponent<InputField>();

	entity = EntityFactory::GenerateButton(Vector2(450, 680), Vector2(96, 32), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Save", 200));
	save = entity->GetComponent<Button>();

	entity = EntityFactory::GenerateButton(Vector2(560, 680), Vector2(96, 32), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Load", 200));
	load = entity->GetComponent<Button>();

	Resume();
}

void TestState::Exit()
{
	if (scene)
	{
		scene->Exit();

		delete scene;
		scene = NULL;
	}
}

void TestState::Update(float dt)
{
	scene->Update(dt);
}

#include "MenuState.h"

void TestState::HandleEvents()
{
	if (menu->IsState())
		Engine.ChangeState(&MenuState::Instance());

	if (load->IsState())
	{
		scene->grid->Load(ToString("Data//Levels//", input->GetOutput(), ".csv").c_str());
	}

	if (save->IsState())
	{
		scene->grid->Save(ToString("Data//Levels//", input->GetOutput(), ".csv").c_str());
	}
}

void TestState::Render()
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

void TestState::Pause()
{
}

void TestState::Resume()
{
	Input.ShowCursor();
	Scene::scene = scene; 
}