#include "EnemyInfoScript.h"

EnemyInfoScript::EnemyInfoScript()
{
}

EnemyInfoScript::~EnemyInfoScript()
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

void EnemyInfoScript::Init(Entity * ent)
{
	StateObject::Init(ent);

	InitEnemy(ent);
}

#include "../../../../../Assets.h"
#include "../../../../../GridInfo.h"
#include "../../../../Tower/TowerDatabase.h"
#include "../../../../Tower/TowerData.h"
#include <vector>

#include "Utility.h"

void EnemyInfoScript::InitEnemy(Entity *ent)
{
	Entity* entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 610), "ENEMIES", 512, true));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

	int count = 1;
	for (int y = 500; y > 150; y -= 50)
	{
		entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.15f, y), ("Tier " + ToString(count)).c_str(), 200, false));
		entity = ent->AttachChild(EntityFactory::CreateSpriteAnimation(
			Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.275f, y),
			Vector2(TileWidth, TileHeight),
			"Jellies",
			("Jellies" + ToString(count)).c_str(),
			Vector4(1, 1, 1, 1),
			4,
			true,
			true));

		entity = ent->AttachChild(EntityFactory::CreateSpriteAnimation(
			Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.4f, y),
			Vector2(TileWidth, TileHeight),
			"Jellies",
			("Jellies" + ToString(count)).c_str(),
			Vector4(1, 1, 1, 1),
			4,
			true,
			true));

		entity = ent->AttachChild(EntityFactory::CreateSpriteAnimation(
			Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.4f, y + 2),
			Vector2(TileWidth * 1.8f, TileHeight * 1.8f),
			"Wings",
			"Wings",
			Vector4(0, 0, 0, 1),
			3,
			true,
			false));

		entity = ent->AttachChild(EntityFactory::CreateSpriteAnimation(
			Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.4f, y - 2),
			Vector2(TileWidth * 1.8f, TileHeight * 1.8f),
			"Wings",
			"Wings",
			Vector4(0, 0, 0, 1),
			3,
			true,
			false));

		entity = ent->AttachChild(EntityFactory::CreateSpriteAnimation(
			Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.4f, y),
			Vector2(TileWidth * 1.75f, TileHeight * 1.75f),
			"Wings",
			"Wings",
			Vector4(1, 1, 1, 1),
			3,
			true,
			false));

		++count;
	}

	for (int y = 500; y > 300; y -= 50)
	{
		entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.55f, y), ("Tier " + ToString(count)).c_str(), 200, false));
		entity = ent->AttachChild(EntityFactory::CreateSpriteAnimation(
			Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.675f, y),
			Vector2(TileWidth, TileHeight),
			"Jellies",
			("Jellies" + ToString(count)).c_str(),
			Vector4(1, 1, 1, 1),
			4,
			true,
			true));

		entity = ent->AttachChild(EntityFactory::CreateSpriteAnimation(
			Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.75f, y),
			Vector2(TileWidth, TileHeight),
			"Jellies",
			("Jellies" + ToString(count)).c_str(),
			Vector4(1, 1, 1, 1),
			4,
			true,
			true));

		entity = ent->AttachChild(EntityFactory::CreateSpriteAnimation(
			Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.75f, y + 2),
			Vector2(TileWidth * 1.8f, TileHeight * 1.8f),
			"Wings",
			"Wings",
			Vector4(0, 0, 0, 1),
			3,
			true,
			false));

		entity = ent->AttachChild(EntityFactory::CreateSpriteAnimation(
			Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.75f, y - 2),
			Vector2(TileWidth * 1.8f, TileHeight * 1.8f),
			"Wings",
			"Wings",
			Vector4(0, 0, 0, 1),
			3,
			true,
			false));

		entity = ent->AttachChild(EntityFactory::CreateSpriteAnimation(
			Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.75f, y),
			Vector2(TileWidth * 1.75f, TileHeight * 1.75f),
			"Wings",
			"Wings",
			Vector4(1, 1, 1, 1),
			3,
			true,
			false));

		++count;
	}

	/*entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.25f, 500), "Bubble Blower", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 500), "Cheap and useful for early stages", 200, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);*/

	/*entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 430), Vector2(TileWidth, TileHeight), Resource.GetTexture("Fountain"), Vector4(1, 1, 1, 1)));
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
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);*/
}

void EnemyInfoScript::Update(double dt)
{
	
}