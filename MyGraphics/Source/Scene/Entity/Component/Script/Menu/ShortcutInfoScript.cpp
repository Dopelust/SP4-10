#include "ShortcutInfoScript.h"

ShortcutInfoScript::ShortcutInfoScript()
{
}

ShortcutInfoScript::~ShortcutInfoScript()
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

void ShortcutInfoScript::Init(Entity * ent)
{
	StateObject::Init(ent);

	InitTowers(ent);
}

#include "../../../../../Assets.h"
#include "../../../../../GridInfo.h"
#include "../../../../Tower/TowerDatabase.h"
#include "../../../../Tower/TowerData.h"
#include <vector>

void ShortcutInfoScript::InitTowers(Entity *ent)
{
	Entity* entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 610), "Shortcuts", 512, true));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.18f, 520), Vector2(TileWidth, TileHeight) * 1.5f, Resource.GetTexture("Bubble Blower"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.21f, 520), "Bubble Blower", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 520), "1", 200, false));

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.18f, 450), Vector2(TileWidth, TileHeight), Resource.GetTexture("Fountain"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.21f, 450), "Fountain", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 450), "2", 200, false));

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.18f, 380), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Sniper"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.21f, 380), "Sniper", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 380), "3", 200, false));

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.18f, 310), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Dispenser"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.21f, 310), "Dispenser", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 310), "4", 200, false));

	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.18f, 240), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Bomber"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.21f, 240), "Bomber", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 240), "5", 200, false));


	entity = ent->AttachChild(EntityFactory::CreateGraphic(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.18f, 170), Vector2(TileWidth, TileHeight) * 1.75f, Resource.GetTexture("Turret"), Vector4(1, 1, 1, 1)));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.21f, 170), "Turret", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.45f, 170), "6", 200, false));

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.61f, 520), "Pause", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.75f, 520), "Spacebar", 200, false));

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.61f, 450), "Upgrade", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.75f, 450), "U", 200, false));

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.61f, 380), "Sell", 300, false));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.75f, 380), "S", 200, false));
}

void ShortcutInfoScript::Update(double dt)
{
	
}