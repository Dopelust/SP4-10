#include "LevelScript.h"

LevelScript::LevelScript()
{
}

LevelScript::~LevelScript()
{
}

#include "../../../../Scene.h"
#include "../../../Entity.h"
#include "../../../EntityFactory.h"
#include "../../Transform.h"

#include "../../GUI/Button.h"
#include "../../GUI/InputField.h"

#include "Vector2.h"
#include "../CSVRenderer.h"
#include "../../TextRenderer2D.h"

#include "MenuHandler.h"
#include "MenuScript.h"

void LevelScript::Init(Entity * ent)
{
	AddLevel("", "", Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.4f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.5f), ent);

	ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.4f - 128, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.725f + 24),
		"Load:", 300))->GetComponent<TextRenderer2D>()->color.Set(0.7f, 0.7f, 0);

	input = ent->AttachChild(EntityFactory::CreateInputField(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.4f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.725f),
		Vector3(0, 0, 0), 16, 256))->GetChild("Input Field")->GetComponent<InputField>();

	Entity* entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.7f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.5f),
		Vector2(204, 40), NULL, Vector3(0.1f, 0.1f, 0.1f), false));
		
	entity = entity->AttachChild(EntityFactory::CreateButton(Vector2(),
		Vector2(200, 36), NULL, Vector3(0.6f, 0.6f, 0.6f), true));

	editor = entity->GetComponent<Button>();
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Level Editor", 200));
}

#include "Utility.h"
#include "FileSystem.h"

#include "../../../../../GameEngine.h"
#include "../../../../../TestState.h"

void LevelScript::Update(double dt)
{
	string& output = input->GetOutput();

	if (output != "level1" &&
		output != "level2" &&
		output != "level3" &&
		output != "level4")
	{
		csv->UploadCSV(ToString("Data//Levels//", output, ".csv").c_str());

		if (File.Exists(ToString("Data//Levels//", output, ".csv").c_str()) && play->IsState())
			PlayLevel(input->GetOutput().c_str());
	}

	if (editor->IsState())
		Engine.PushState(&TestState::Instance());
}

#include "../../../../../Assets.h"

void LevelScript::AddLevel(const char * name, const char * level, const Vector2 & position, Entity* owner)
{
	Entity* entity = LevelSelectObject::AddLevel(name, level, position, owner);

	csv = entity->GetComponent<CSVRenderer>();

	play = entity->AddComponent<Button>();
	play->SetGraphic(csv);
}
