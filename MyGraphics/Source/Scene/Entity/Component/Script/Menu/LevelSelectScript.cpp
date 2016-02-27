#include "LevelSelectScript.h"

LevelSelectScript::LevelSelectScript()
{
}

LevelSelectScript::~LevelSelectScript()
{
}

#include "../../../../Scene.h"
#include "../../../Entity.h"
#include "../../../EntityFactory.h"
#include "../../Transform.h"

#include "../../GUI/Button.h"
#include "../../GUI/Slider.h"

#include "Vector2.h"

void LevelSelectScript::Init(Entity * ent)
{
	MenuObject::Init(ent);

	Entity* entity = ent->AttachChild(EntityFactory::CreateButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.33f, 500), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f)));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Level 1", 128));
	level1 = entity->GetComponent<Button>();

	entity = ent->AttachChild(EntityFactory::CreateButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.66f, 500), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f)));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Level 2", 128));
	level2 = entity->GetComponent<Button>();

	entity = ent->AttachChild(EntityFactory::CreateButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.33f, 300), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f)));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Level 3", 128));
	level3 = entity->GetComponent<Button>();

	entity = ent->AttachChild(EntityFactory::CreateButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.66f, 300), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f)));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Level 4", 128));
	level4 = entity->GetComponent<Button>();

	entity = ent->AttachChild(EntityFactory::CreateButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 200), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f)));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "Custom Level", 128));
	custom = entity->GetComponent<Button>();

	entity = ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 100), "BACK", 400, Vector3(0.7f, 0.7f, 0)));
	back = entity->GetComponent<Button>();

	position.Set(Scene::scene->GetResolutionX(Scene::scene->canvas), 0);
	transform->Position() = position.GetVector3();

	rate = 10;
}

#include "MenuHandler.h"
#include "MenuScript.h"
#include "../../../../../GameEngine.h"
#include "../../../../../TestState.h"
#include "../../../../../PlayState.h"

void LevelSelectScript::Update(double dt)
{
	MenuObject::Update(dt);

	if (level1->IsState())
		PlayLevel("level1");

	if (level2->IsState())
		PlayLevel("level2");

	if (level3->IsState())
		PlayLevel("level3");

	if (level4->IsState())
		PlayLevel("level4");

	if (custom->IsState())
		PlayLevel(NULL);

	if (back->IsState())
		menu->Switch(menu->menu);
}

#include "FileSystem.h"

void LevelSelectScript::PlayLevel(const char * level)
{
	File.Remove("Data//Save//save.txt");
	Engine.ChangeState(&PlayState::Instance());
}
