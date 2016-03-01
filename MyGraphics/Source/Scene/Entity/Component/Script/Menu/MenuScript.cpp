#include "MenuScript.h"

MenuScript::MenuScript()
{
}

MenuScript::~MenuScript()
{
}

#include "../../../../Scene.h"
#include "../../../Entity.h"
#include "../../../EntityFactory.h"
#include "../../Transform.h"
#include "../../TextRenderer2D.h"

#include "Vector2.h"
#include "../../GUI/Button.h"
#include "FileSystem.h"

void MenuScript::Init(Entity * ent)
{
	StateObject::Init(ent);

	Entity* entity =
		ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 600), "NIGHT CHANGES", 800));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.7f, 0.7f, 0);

	entity =
		ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 450), "PLAY", 400, Vector3(0.7f, 0.7f, 0)));
	play = entity->GetComponent<Button>();

	entity =
		ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 390), "CONTINUE", 400, Vector3(0.7f, 0.7f, 0)));
	resume = entity->GetComponent<Button>();

	if (File.Exists("Data//Save//save.txt"))
		resume->Enable();
	else
		resume->Disable();

	entity =
		ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 330), "LEVEL EDITOR", 400, Vector3(0.7f, 0.7f, 0)));
	editor = entity->GetComponent<Button>();

	entity =
		ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 270), "OPTIONS", 400, Vector3(0.7f, 0.7f, 0)));
	option = entity->GetComponent<Button>();

	entity =
		ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 210), "STATS", 400, Vector3(0.7f, 0.7f, 0)));
	achievement = entity->GetComponent<Button>();

	entity =
		ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 150), "QUIT", 400, Vector3(0.7f, 0.7f, 0)));
	exit = entity->GetComponent<Button>();

	target.Set(-Scene::scene->GetResolutionX(Scene::scene->canvas), 0);
	transform->Position() = target.GetVector3();

	rate = 16;
}

#include "MenuHandler.h"
#include "OptionScript.h"
#include "LevelHandler.h"
#include "AchievementScript.h"

#include "../../GUI/Button.h"
#include "../../../../../GameEngine.h"
#include "../../../../../TestState.h"
#include "../../../../../PlayState.h"

void MenuScript::Update(double dt)
{
	StateObject::Update(dt);

	if (play->IsState())
		menu->Push(menu->GetState<LevelHandler>());

	else if (resume->IsState())
		Engine.ChangeState(&PlayState::Instance());

	else if (editor->IsState())
		Engine.ChangeState(&TestState::Instance());

	else if (option->IsState())
		menu->Push(menu->GetState<OptionScript>());

	else if (achievement->IsState())
	{
		menu->Push(menu->GetState<AchievementScript>());
		menu->GetState<AchievementScript>()->LoadAchievements("Data//Save//achievementStats.txt");
	}

	if (exit->IsState())
		Engine.Terminate();
}
