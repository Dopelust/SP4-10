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
#include "Scene\Entity\Component\Script\HoverText.h"

#include "Screen.h"

void TestState::Init()
{
	glClearColor(0.2, 0.2, 0.2, 1);

	scene = new Scene("Data//Scene//Test");
	scene->CreateSpatialPartition(Scene::GRID_3D_VOXEL);
	scene->camera.position.Set(0, 0, 0);

	scene->root->AddComponent<WorldZoomScript>();

	Entity* editor = scene->root->AttachChild(EntityFactory::CreateSprite(Vector2(TileWidth * 0.5f, TileHeight * 0.5f), Vector2(TileWidth, TileHeight), NULL, Vector4(1, 1, 1, 0.5f)));
	editor->AddComponent<TileSelector>();
	
	{
		Entity* entity = scene->canvas->AddChild("Hotbar");
		entity->transform->SetPosition(1200, 630);
		entity->AddComponent<TileEditorGUI>()->SetEditor(editor->AddComponent<TileEditor>());

		for (int i = 0; i < 5; ++i)
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateButton(Vector2(0, -64 * i), Vector2(48, 48), NULL, Vector3(0.65f, 0.65f, 0.65f)));
			child->AttachChild(EntityFactory::CreateSprite(Vector2(0, 0), Vector2(42, 42), Resource.GetSpritesheet("Tileset")->GetSprite(i), Vector4(1, 1, 1)));

			entity->GetComponent<TileEditorGUI>()->AddButton(child->GetComponent<Button>());
		}

		entity->GetComponent<TileEditorGUI>()->select = entity->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(48, 48), NULL, Vector4(1, 1, 1)));

		Entity* hover = EntityFactory::GenerateGraphic(Vector2(), Vector2(), NULL, Vector4(0, 0, 0, 0.75f), 1);
		hover->AddComponent<HoverText>()->text = hover->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "", 200, false));
		entity->GetComponent<TileEditorGUI>()->hover = hover->GetComponent<HoverText>();
	}

	Entity* entity = EntityFactory::GenerateGraphic(Vector2(Screen.GetProjectionWidth() - 24, Screen.GetProjectionHeight() - 24), Vector2(32, 32), NULL, Vector3(0.1f, 0.1f, 0.1f), false);
	entity = entity->AttachChild(EntityFactory::CreateButton(Vector2(), Vector2(28, 28), NULL, Vector3(0.75f, 0, 0), 200));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "X", 200));
	menu = entity->GetComponent<Button>();

	entity = EntityFactory::GenerateInputField(Vector2(256, 680), Vector3(0, 0, 0), 16, 200);
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(-220, 0), "File:", 256, false));
	input = entity->GetChild("Input Field")->GetComponent<InputField>();

	entity = EntityFactory::GenerateButton(Vector2(450, 680), Vector2(96, 32), NULL, Vector3(0.5f, 0.5f, 0.5f), true);
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Save", 200));
	save = entity->GetComponent<Button>();

	entity = EntityFactory::GenerateButton(Vector2(560, 680), Vector2(96, 32), NULL, Vector3(0.5f, 0.5f, 0.5f), true);
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Load", 200));
	load = entity->GetComponent<Button>();

	entity = EntityFactory::GenerateButton(Vector2(670, 680), Vector2(96, 32), NULL, Vector3(0.5f, 0.5f, 0.5f), true);
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Delete", 200));
	remove = entity->GetComponent<Button>();

	popup = EntityFactory::GeneratePopup(Vector2(300, 150), "", 150);
	popup->SetActive(false);

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

#include "MenuState.h"
#include "Scene\Entity\Component\Script\StandardPopup.h"
#include "Scene\Entity\Component\TextRenderer2D.h"

void TestState::Update(float dt)
{
	scene->Update(dt);

	if (popup->IsActive())
	{
		if (popup->GetComponent<StandardPopup>()->IsOK())
		{
			string text = popup->GetComponent<StandardPopup>()->text->GetText();

			if (text == "Save?" || text == "Overwrite existing data?")
			{
				scene->grid->Save(ToString("Data//Levels//", input->GetOutput(), ".csv").c_str());
			}
			else if (text == "Load?")
			{
				scene->grid->Load(ToString("Data//Levels//", input->GetOutput(), ".csv").c_str());
			}
			else if (text == "Delete?")
			{
				File.Remove(ToString("Data//Levels//", input->GetOutput(), ".csv").c_str());
				scene->grid->Reset();
				input->SetOutput("");
			}
			else if (text == "Quit?")
			{
				Engine.PopState();
				return;
			}

			popup->GetComponent<StandardPopup>()->Close();
		}
	}
	
	if (menu->IsState())
	{
		popup->GetComponent<StandardPopup>()->PopUp("Quit?");
	}

	if (load->IsState())
	{
		string& output = input->GetOutput();

		if (!File.Exists(ToString("Data//Levels//", input->GetOutput(), ".csv").c_str()))
			popup->GetComponent<StandardPopup>()->PopUp("Level does not exist.");
		else
			popup->GetComponent<StandardPopup>()->PopUp("Load?");
	}

	if (save->IsState())
	{
		if (!File.Exists(ToString("Data//Levels//", input->GetOutput(), ".csv").c_str()))
			popup->GetComponent<StandardPopup>()->PopUp("Save?");
		else
			popup->GetComponent<StandardPopup>()->PopUp("Overwrite existing data?");
	}

	if (remove->IsState())
	{
		string& output = input->GetOutput();

		if (!File.Exists(ToString("Data//Levels//", input->GetOutput(), ".csv").c_str()))
			popup->GetComponent<StandardPopup>()->PopUp("Level does not exist.");
		else if (output == "level1" ||
				output == "level2" ||
				output == "level3" ||
				output == "level4")
			popup->GetComponent<StandardPopup>()->PopUp("Cannot delete this level.");
		else
			popup->GetComponent<StandardPopup>()->PopUp("Delete?");
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