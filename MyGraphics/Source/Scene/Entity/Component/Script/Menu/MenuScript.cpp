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
	MenuObject::Init(ent);

	Entity* entity =
		ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 600), "NIGHT CHANGES", 800));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.7f, 0.7f, 0);

	entity =
		ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 450), "PLAY", 400, Vector3(0.7f, 0.7f, 0)));
	play = entity->GetComponent<Button>();

	entity =
		ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 375), "CONTINUE", 400, Vector3(0.7f, 0.7f, 0)));
	resume = entity->GetComponent<Button>();

	if (File.Exists("Data//Save//save.txt"))
		resume->Enable();
	else
		resume->Disable();

	entity =
		ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 300), "LEVEL EDITOR", 400, Vector3(0.7f, 0.7f, 0)));
	editor = entity->GetComponent<Button>();

	entity =
		ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 225), "OPTIONS", 400, Vector3(0.7f, 0.7f, 0)));
	option = entity->GetComponent<Button>();

	entity =
		ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 150), "QUIT", 400, Vector3(0.7f, 0.7f, 0)));
	exit = entity->GetComponent<Button>();

	position.Set(-Scene::scene->GetResolutionX(Scene::scene->canvas), 0);
	transform->Position() = position.GetVector3();

	rate = 10;
}

#include "MenuHandler.h"
#include "OptionScript.h"
#include "LevelSelectScript.h"

#include "../../GUI/Button.h"
#include "../../../../../GameEngine.h"
#include "../../../../../TestState.h"
#include "../../../../../PlayState.h"

void MenuScript::Update(double dt)
{
	MenuObject::Update(dt);

	if (play->IsState())
		menu->Switch(menu->levelselect);

	if (resume->IsState())
		Engine.ChangeState(&PlayState::Instance());

	if (editor->IsState())
		Engine.ChangeState(&TestState::Instance());

	if (option->IsState())
		menu->Switch(menu->option);

	if (exit->IsState())
		Engine.Terminate();
}
