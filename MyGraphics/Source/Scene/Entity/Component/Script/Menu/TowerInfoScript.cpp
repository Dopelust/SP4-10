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

	InitTowers(ent);
}

#include "../../../../../Assets.h"
#include "../../../../../GridInfo.h"
#include "../../../../Tower/TowerDatabase.h"
#include "../../../../Tower/TowerData.h"
#include <vector>

void TowerInfoScript::InitTowers(Entity *ent)
{
	Entity* entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 610), "TOWERS", 512, true));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.18f, 520), Vector2(TileWidth, TileHeight) * 1.5f, Resource.GetTexture("Bubble Blower"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.21f, 520), "Bubble Blower", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 520), "Cheap and useful for early stages", 200, false));

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.18f, 450), Vector2(TileWidth, TileHeight), Resource.GetTexture("Fountain"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.21f, 450), "Fountain", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 450), "Shoots projectiles in fixed directions", 200, false));

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.18f, 380), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Sniper"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.21f, 380), "Sniper", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 380), "Pops enemies by multiple tiers", 200, false));

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.18f, 310), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Dispenser"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.21f, 310), "Dispenser", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 310), "Shoots many projectiles quickly", 200, false));

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.18f, 240), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Gun"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.21f, 240), "Cannon", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 240), "Shoots projectiles which stuns", 200, false));


	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.18f, 170), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Gun"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.21f, 170), "Turret", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 170), "Shoots projectiles which slows", 200, false));
}

void TowerInfoScript::Update(double dt)
{
	
}