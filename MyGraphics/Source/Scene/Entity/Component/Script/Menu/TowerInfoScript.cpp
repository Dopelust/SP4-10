#include "TowerInfoScript.h"

TowerInfoScript::TowerInfoScript()
{
}

TowerInfoScript::~TowerInfoScript()
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
#include "PageSystem.h"
#include "StateObject.h"

void TowerInfoScript::Init(Entity * ent)
{
	StateObject::Init(ent);

	/*Entity* entity = ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 70), "BACK", 400, Vector3(0.7f, 0.7f, 0)));
	back = entity->GetComponent<Button>();*/

	InitTowers(ent);
}

#include "../../../../../Assets.h"
#include "../../../../../GridInfo.h"
#include "../../../../Tower/TowerDatabase.h"
#include "../../../../Tower/TowerData.h"
#include <vector>

void TowerInfoScript::InitTowers(Entity *ent)
{
	Entity *entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 650), "NOTEBOOK", 400, true));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 600), "TOWERS", 200, true));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 500), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Bubble Blower"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.25f, 500), "Bubble Blower", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 500), "Cheap and useful for early stages", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 430), Vector2(TileWidth, TileHeight), Resource.GetTexture("Fountain"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.25f, 430), "Fountain", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 430), "Shoots projectiles in fixed directions", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 360), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Sniper"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.25f, 360), "Sniper", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 360), "Pops enemies by multiple tiers", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);


	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 290), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Dispenser"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.25f, 290), "Dispenser", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 290), "Shoots many projectiles quickly", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);


	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 220), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Gun"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.25f, 220), "Cannon", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 220), "Shoots projectiles which stuns", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);


	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 150), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Gun"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.25f, 150), "Turret", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 150), "Shoots projectiles which slows", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
}

void TowerInfoScript::Update(double dt)
{
	
}