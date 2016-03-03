#include "TileInfoScript.h"

#include "../../Transform.h"
#include "../../../Entity.h"
#include "../../../EntityFactory.h"
#include "../../GUI/Button.h"
#include "../../Graphic2D.h"

#include "../../../../../Assets.h"
#include "../../../../../Spritesheet.h"
#include "../../../../../Sprite.h"
#include "../../../../Scene.h"
#include "../../TextRenderer2D.h"

TileInfoScript::TileInfoScript() : select(NULL), first(NULL)
{
}

TileInfoScript::~TileInfoScript()
{
}

void TileInfoScript::Init(Entity* entity)
{
	Entity* child = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 610), "TILES", 512, true));
	child->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

	{
		for (int i = -2; i <= 2; ++i)
		{
			Entity* child = entity->AttachChild(EntityFactory::CreateButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.24f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.5f - i * 80), Vector2(72, 72), NULL, Vector3(0.7f, 0.7f, 0.7f)));
			child->AttachChild(EntityFactory::CreateSprite(Vector2(0, 0), Vector2(64, 64), Resource.GetSpritesheet("Tileset")->GetSprite(i + 2), Vector4(1, 1, 1)));

			Entity* info = entity->AddChild("Information");

			switch (i + 2)
			{
			case 0:
			{
				first = info;

				Entity* text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.55f),
					"Floor", 400, true));
				text->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

				text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.475f),
					"Empty tile for enemies to walk on and", 200, true));
				text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.475f - 32),
					"towers to be placed on.", 200, true));
			}
				break;
			case 2:
			{
				Entity* text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.55f),
					"Wall", 400, true));
				text->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

				text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.475f),
					"Tile that blocks the path of enemies and", 200, true));
				text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.475f - 32),
					"the placing of towers.", 200, true));
			}
				break;
			case 1:
			{
				Entity* text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.55f),
					"Hole", 400, true));
				text->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

				text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.475f),
					"Void tile that blocks the path of enemies", 200, true));
				text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.475f - 32),
					"and the placing of towers.", 200, true));
			}
				break;
			case 3:
			{
				Entity* text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.55f),
					"Entrance", 400, true));
				text->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

				text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.475f),
					"Tile that enemies spawn on and", 200, true));
				text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.475f - 32),
					"blocks the placing of towers.", 200, true));
			}
				break;
			case 4:
			{
				Entity* text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.55f),
					"Exit", 400, true));
				text->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

				text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.475f),
					"Tile that you have to prevent enemies from", 200, true));
				text = info->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.58f, Scene::scene->GetResolutionY(Scene::scene->canvas) * 0.475f - 32),
					"reaching and blocks the placing of towers.", 200, true));
			}
				break;
			}

			AddButton(child->GetComponent<Button>(), info);
		}

		select = entity->AttachChild(EntityFactory::CreateGraphic(Vector2(), Vector2(72, 72), NULL, Vector4(1, 1, 1)));

		Show(first);
	}
}

void TileInfoScript::Update(double dt)
{
	for (auto& button : buttonMap)
	{
		if (button.first->IsState(Button::STATE_CLICK))
		{
			Show(button.second);
			break;
		}
	}
}

void TileInfoScript::AddButton(Button * button, Entity* info)
{
	buttonMap[button] = info;
}

#include "../../SpriteRenderer.h"

void TileInfoScript::Show(Entity* info)
{
	for (auto& button : buttonMap)
	{
		if (button.second == info)
		{
			button.second->SetActive(true);

			if (select)
				select->transform->Position() = button.first->transform->Position();
		}
		else
			button.second->SetActive(false);
	}
}
