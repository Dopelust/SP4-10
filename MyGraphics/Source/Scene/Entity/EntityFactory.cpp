#include "EntityFactory.h"
#include "Entity.h"
#include "../Scene.h"
#include "../../Assets.h"
#include "../../Spritesheet.h"
#include "Utility.h"
#include "../Camera.h"
#include "Component\Transform.h"
#include "Component\Graphic2D.h"
#include "Component\SpriteRenderer.h"
#include "Component\SpriteAnimator.h"
#include "Component\TextRenderer2D.h"
#include "Component\GUI\Button.h"
#include "Component\GUI\Toggle.h"
#include "Component\GUI\InputField.h"
#include "Component\Physics\BoxCollider.h"
#include "Component\Physics\RigidBody.h"
#include "Component\NetworkObject.h"
#include "Component\AI\BasicAI.h"	
#include "Component\GUI\Slider.h"

Assets& EntityFactory::assets = Assets::Instance();
map<Entity*, vector<Entity*>> EntityFactory::toGenerate;
map<Entity*, vector<Entity*>> EntityFactory::toDestroy;

#define scene Scene::scene

Entity* EntityFactory::GeneratePlayer()
{
	return NULL;
}

Entity * EntityFactory::GenerateButton(const Vector2 & position, const Vector2 & size, Texture * texture, const Vector3& color)
{
	return Generate(scene->canvas, CreateButton(position, size, texture, color));
}

#include "../../FontManager.h"
#include "../../Font.h"

Entity* EntityFactory::GenerateInputField(const Vector2& position, const Vector3& color, int limit, float textSize)
{
	Vector2 size = FontManager::Instance().GetFont()->GetTextSize("O") * textSize;
	size.x *= (limit + 1);
	size.y *= 1.3f;

	Entity* entity = new Entity("Input");
	entity->transform->SetPosition(position.x, position.y);
	entity->transform->SetSize(size.x + 4, size.y + 4);

	entity->AddComponent<Graphic2D>();

	Entity* button = entity->AttachChild(CreateButton(Vector2(), size, NULL, Vector3(color.x, color.y, color.z)));

	Entity* child = entity->AddChild("Input Field");
	child->transform->SetPosition(-size.x * 0.5f, -size.y * 0.1f, 0);
	child->transform->SetSize(textSize);
	child->AddComponent<TextRenderer2D>()->SetAlignCenter(false);

	child->AddComponent<InputField>()->SetLimit(limit);
	child->GetComponent<InputField>()->SetActivator(button->GetComponent<Button>());
	child->GetComponent<InputField>()->SetTextRenderer(child->GetComponent<TextRenderer2D>());

	Entity* ticker = child->AddChild("Ticker");
	ticker->transform->SetPosition(0, size.y * 0.1f, 0);
	ticker->transform->SetSize(2, size.y * 0.8f);
	ticker->AddComponent<Graphic2D>();

	child->GetComponent<InputField>()->SetTicker(ticker);

	Generate(scene->canvas, entity);
	return entity;
}

Entity * EntityFactory::GenerateTextGUI(const Vector2 & position, const char* text, float size)
{
	return Generate(scene->canvas, CreateTextGUI(position, text, size));
}

#include "Component\GUI\Checkbox.h"

Entity * EntityFactory::CreateSlider(const Vector2 & position, const Vector2 & size, const char * tag, float min, float value, float max, bool integer)
{
	Entity* entity = CreateGraphic(position, size + Vector2(4, 4), NULL, Vector3(0, 0, 0));

	Entity* guide = entity->AttachChild(CreateButton(Vector2(), Vector2(size.x, 20), NULL, Vector3(0, 0, 0)));
	guide->GetComponent<Graphic2D>()->SetActive(false);

	Entity* fill = entity->AttachChild(CreateGraphic(Vector2(), size, NULL, Vector3(0.75f, 0, 0)));

	Entity* slider = entity->AttachChild(CreateButton(Vector2(), Vector2(8, 20), NULL, Vector3(0, 0, 0)));
	slider->Rename("Slider");
	slider->AddComponent<Slider>()->guide = guide->GetComponent<Button>();
	slider->GetComponent<Slider>()->fill = fill->transform;

	Entity* text = entity->AttachChild(CreateTextGUI(Vector2(-size.x *0.5f, 24), tag, 150));
	text->GetComponent<TextRenderer2D>()->SetAlignCenter(false);

	text = entity->AttachChild(CreateTextGUI(Vector2(size.x * 0.5f + 16, 0), "", 200));
	text->GetComponent<TextRenderer2D>()->SetAlignCenter(false);

	if (!integer)
		slider->GetComponent<Slider>()->valueType = Slider::SLIDER_FLOAT;

	slider->GetComponent<Slider>()->SetText(text->GetComponent<TextRenderer2D>());
	slider->GetComponent<Slider>()->SetMin(min);
	slider->GetComponent<Slider>()->SetMax(max);
	slider->GetComponent<Slider>()->SetValue(value);

	slider = slider->AttachChild(CreateGraphic(Vector2(), Vector2(4, 16), NULL, Vector3(0.9f, 0.9f, 0.9f)));

	return entity;
}

Entity * EntityFactory::CreateCheckbox(const Vector2 & position, float size, float stroke, const char * text, bool * toggle)
{
	Entity* entity = CreateGraphic(position, Vector2(size + stroke, size + stroke), NULL, Vector3(0.9f, 0.9f, 0.9f));

	Entity* t = CreateTextGUI(Vector2(size, 0), text, 256);
	t->GetComponent<TextRenderer2D>()->SetAlignCenter(false);

	entity->AttachChild(t);

	Entity* button = entity->AttachChild(CreateButton(Vector2(), Vector2(size, size), NULL, Vector3(0.2f, 0.2f, 0.2f)));
	button->AddComponent<Toggle>()->SetToggle(toggle);

	button->AddComponent<Checkbox>()->check = button->AttachChild(CreateGraphic(Vector2(), Vector2(size * 0.5f, size * 0.5f), NULL, Vector3(0.9f, 0.9f, 0.9f)));
	button->GetComponent<Checkbox>()->check->Rename("Check");

	return entity;
}

Entity * EntityFactory::CreateGraphic(const Vector2 & position, const Vector2 & size, Texture * texture, const Vector4 & color)
{
	Entity* entity = new Entity("Graphic");
	entity->transform->SetPosition(position.x, position.y);
	entity->transform->SetSize(size.x, size.y);

	entity->AddComponent<Graphic2D>()->SetTexture(texture);
	entity->GetComponent<Graphic2D>()->SetColor(color.x, color.y, color.z, color.w);

	return entity;
}

Entity * EntityFactory::CreateButton(const Vector2 & position, const Vector2 & size, Texture * texture, const Vector3 & color)
{
	Entity* entity = CreateGraphic(position, size, texture, color);
	entity->AddComponent<Button>();

	entity->Rename("Button");

	return entity;
}

Entity * EntityFactory::CreateTextGUI(const Vector2 & position, const char * text, float size, bool alignCenter)
{
	Entity* entity = new Entity("Text");

	entity->transform->SetPosition(position.x, position.y);
	entity->transform->SetSize(size);

	entity->AddComponent<TextRenderer2D>()->SetText(text);
	entity->GetComponent<TextRenderer2D>()->SetAlignCenter(alignCenter);

	return entity;
}

#include "../../GridInfo.h"
#include "../../Grid.h"
#include "../Entity/Component/Script/TowerController.h"
#include "Vector3.h"

Entity* EntityFactory::GenerateTower(const Vector2& position, string type)
{
	Entity* entity = CreateGraphic(position, Vector2(TileWidth, TileHeight), NULL, Vector4(1, 1, 1, 1));
	Vector3 index = scene->grid->GetIndex(entity->transform->GetPosition());

	entity->AddComponent<TowerController>()->index = Vector2(index.x, index.y);
	entity->GetComponent<TowerController>()->Init(type);

	Generate(scene->root, entity);
	return entity;
}

#include "Component\Script\ProjectileController.h"

Entity* EntityFactory::GenerateProjectile(const Vector2& position, string type, const Vector2& velocity)
{
	Entity* entity = CreateGraphic(position, Vector2(TileWidth, TileHeight), NULL, Vector4(1, 1, 1, 1));

	//entity->AddComponent<Projectile>()->LateInit(type, velocity.GetVector3());

	Generate(scene->root, entity);
	return entity;
}

#include "Component\Script\PathFinder.h"

Entity* EntityFactory::GeneratePathFinder()
{
	Entity* entity;
	entity = new Entity();
	entity->AddComponent<PathFinder>();

	Generate(scene->root, entity);

	return entity;
}

#include "Component\Script\EnemyController.h"

Entity* EntityFactory::GenerateEnemy(const Vector2& position, string enemyTexture, int enemyTier, float enemySpeed)
{
	Entity* entity = CreateGraphic(position, Vector2(TileWidth, TileHeight), NULL, Vector4(1, 1, 1, 1));
	entity->AddComponent<EnemyController>()->LateInit(enemyTexture, enemyTier, enemySpeed);

	Generate(scene->root, entity);
	return entity;
}

Entity * EntityFactory::Generate(Entity * root, Entity * entity)
{
	if (entity)
		toGenerate[root].push_back(entity);

	return entity;
}

void EntityFactory::Destroy(Entity * entity)
{
	if (entity)
	{
		for (auto& ent : toDestroy[entity->parent])
		{
			if (entity == ent)
				return;
		}

		toDestroy[entity->parent].push_back(entity);
	}
}

void EntityFactory::GenerateEntities()
{
	if (toGenerate.size() > 0)
	{
		for (auto& root : toGenerate)
		{
			for (auto& child : root.second)
				root.first->AttachChild(child);
		}

		toGenerate.clear();
	}
}

void EntityFactory::DestroyEntities()
{
	if (toDestroy.size() > 0)
	{
		for (auto& root : toDestroy)
		{
			for (auto& child : root.second)
			{
				if (child)
				{
					if (root.first->RemoveChild(child))
						delete child;
				}
			}
		}

		toDestroy.clear();
	}
}
