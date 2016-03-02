#include "../../../../Scene.h"
#include "../../../Entity.h"
#include "../../../EntityFactory.h"
#include "../../Transform.h"
#include "PageSystem.h"

#include "Vector2.h"

#include "InfoHandler.h"
#include "StateObject.h"
#include "MenuHandler.h"

#include "TowerInfoScript.h"
#include "EnemyInfoScript.h"

#include "../../GUI/Button.h"
#include "../../../../../SoundEngine.h"
#include "../../TextRenderer2D.h"

InfoHandler::InfoHandler()
{
}

InfoHandler::~InfoHandler()
{
}

void InfoHandler::Init(Entity * ent)
{
	StateObject::Init(ent);

	page = ent->AddComponent<PageSystem>();

	Entity* entity = ent->AddChild("Page 1");
	entity->AddComponent<TowerInfoScript>();

	page->AddPage(entity);

	entity = ent->AddChild("Page 2");
	entity->AddComponent<EnemyInfoScript>();

	page->AddPage(entity);

	entity = ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 100), "BACK", 400, Vector3(0.7f, 0.7f, 0)));
	back = entity->GetComponent<Button>();

	entity = ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.1f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.5f),
		"<", 1000, Vector3(0.7f, 0.7f, 0)));
	prev = entity->GetComponent<Button>();

	entity = ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.9f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.5f),
		">", 1000, Vector3(0.7f, 0.7f, 0)));
	next = entity->GetComponent<Button>();

	target.Set(Scene::scene->GetResolutionX(Scene::scene->canvas), 0);
	transform->Position() = target.GetVector3();

	rate = 16;
}

void InfoHandler::Update(double dt)
{
	StateObject::Update(dt);

	if (page->HasNextPage())
		next->Enable();
	else
		next->Disable();

	if (page->HasPreviousPage())
		prev->Enable();
	else
		prev->Disable();

	if (next->IsState())
		page->NextPage();
	if (prev->IsState())
		page->PreviousPage();

	if (back->IsState())
	{
		menu->Pop();
		//page->SetPage(0);
	}
}
