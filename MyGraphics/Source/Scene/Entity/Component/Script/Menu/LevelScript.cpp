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
	AddLevel("Load Level", "", Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.6f), ent);

	input = ent->AttachChild(EntityFactory::CreateInputField(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.35f),
		Vector3(0, 0, 0), 16, 256))->GetChild("Input Field")->GetComponent<InputField>();
}

#include "Utility.h"

void LevelScript::Update(double dt)
{
	csv->UploadCSV(ToString("Data//Levels//", input->GetOutput(), ".csv").c_str());

	if (play->IsState())
		PlayLevel(input->GetOutput().c_str());
}

void LevelScript::AddLevel(const char * name, const char * level, const Vector2 & position, Entity* owner)
{
	Entity* entity = LevelSelectObject::AddLevel(name, level, position, owner);

	csv = entity->GetComponent<CSVRenderer>();

	play = entity->AddComponent<Button>();
	play->SetGraphic(csv);
}
