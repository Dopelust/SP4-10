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

Entity* EntityFactory::GenerateSlider(const Vector2 & position, const Vector2 & size, const char* tag, Texture * texture, float min, float value, float max,bool integer)
{
	return Generate(scene->canvas, CreateSlider(position,size,tag,min,value,max,integer));
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

	Entity* guide = entity->AttachChild(CreateButton(Vector2(), Vector2(size.x, size.y), NULL, Vector3(0, 0, 0)));
	guide->GetComponent<Graphic2D>()->SetActive(false);

	Entity* fill = entity->AttachChild(CreateGraphic(Vector2(), size, NULL, Vector3(0.75f, 0, 0)));

	Entity* slider = entity->AttachChild(CreateButton(Vector2(), Vector2(8, size.y), NULL, Vector3(0, 0, 0)));
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

	slider = slider->AttachChild(CreateGraphic(Vector2(), Vector2(4, size.y), NULL, Vector3(0.9f, 0.9f, 0.9f)));

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

Entity * EntityFactory::CreateSprite(const Vector2 & position, const Vector2 & size, Sprite * sprite, const Vector4 & color, int layer)
{
	Entity* entity = new Entity("Sprite");
	entity->transform->SetPosition(position.x, position.y);
	entity->transform->SetSize(size.x, size.y);

	entity->AddComponent<SpriteRenderer>()->SetSprite(sprite);
	entity->GetComponent<SpriteRenderer>()->color = color;
	entity->GetComponent<SpriteRenderer>()->SetLayer(layer);

	return entity;
}

Entity * EntityFactory::CreateGraphic(const Vector2 & position, const Vector2 & size, Texture * texture, const Vector4 & color, int layer)
{
	Entity* entity = new Entity("Graphic");
	entity->transform->SetPosition(position.x, position.y);
	entity->transform->SetSize(size.x, size.y);

	entity->AddComponent<Graphic2D>()->SetTexture(texture);
	entity->GetComponent<Graphic2D>()->SetColor(color.x, color.y, color.z, color.w);
	entity->GetComponent<Graphic2D>()->SetLayer(layer);
	
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

Entity * EntityFactory::GenerateGraphic(const Vector2 & position, const Vector2 & size, Texture * texture, const Vector4 & color, int layer)
{
	return Generate(scene->canvas, CreateGraphic(position, size, texture, color, layer));
}

Entity* EntityFactory::GenerateTower(const Vector2& position, string type)
{
	Entity* entity = CreateGraphic(position, Vector2(TileWidth, TileHeight), NULL, Vector4(1, 1, 1, 1), 3);
	Vector3 index = scene->grid->GetIndex(entity->transform->GetPosition());

	entity->AddComponent<TowerController>()->index = Vector2(index.x, index.y);
	entity->GetComponent<TowerController>()->Init(type);

	if (type == "archer")
	{
		entity->GetComponent<Graphic2D>()->SetTexture(Resource.GetTexture("Archer"));
		entity->transform->Size() *= 1.75f;

		entity->AttachChild(CreateGraphic(Vector2(), Vector2(TileWidth * 1.3f, TileHeight * 1.3f), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));
	}
	else if (type == "sniper")
	{
		entity->GetComponent<Graphic2D>()->SetTexture(Resource.GetTexture("Sniper"));
		entity->transform->Size() *= 2.5f;

		entity->AttachChild(CreateGraphic(Vector2(), Vector2(TileWidth * 1.3f, TileHeight * 1.3f), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));
	}
	else if (type == "fountain")
	{
		entity->GetComponent<Graphic2D>()->SetTexture(Resource.GetTexture("Fountain"));
		entity->transform->Size() *= 1.1f;

		entity->AttachChild(CreateGraphic(Vector2(), Vector2(TileWidth * 1.1f, TileHeight * 1.1f), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));
	}
	else if (type == "dispenser")
	{
		entity->GetComponent<Graphic2D>()->SetTexture(Resource.GetTexture("Dispenser"));
		entity->transform->Size() *= 1.75f;

		entity->AttachChild(CreateGraphic(Vector2(), Vector2(TileWidth * 0.8f, TileHeight * 0.8f), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));
	}

	Entity* child = entity->AttachChild(CreateSprite(Vector2(TileWidth * 0.5f - 6, TileHeight * -0.5f + 8), Vector2(16, 16), Resource.GetSpritesheet("Rank")->GetSprite(0), Vector4(1, 1, 1, 1), 4));
	entity->GetComponent<TowerController>()->rank = child->GetComponent<SpriteRenderer>();

	Generate(scene->root, entity);
	return entity;
}

#include "Component\Script\ProjectileController.h"

Entity* EntityFactory::GenerateProjectile(const Vector2& position, string type)
{
	Entity* entity = CreateGraphic(position, Vector2(), Resource.GetTexture(type.c_str()), Vector4(1, 1, 1, 1));

	if (type == "Bubble")
	{
		entity->transform->SetSize(TileWidth * 0.5f, TileHeight * 0.5f);
		entity->AddComponent<BoxCollider>()->size = Vector3(TileWidth * 0.4f, TileHeight * 0.4f, 0);
	}
	else
	{
		entity->transform->SetSize(TileWidth * 0.9f, TileHeight * 0.9f);
		entity->AddComponent<BoxCollider>()->size = Vector3(TileWidth * 0.2f, TileHeight * 0.2f, 0);
	}

	entity->AddComponent<RigidBody>();
	entity->AddComponent<Projectile>()->LateInit(type);

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

Entity* EntityFactory::GenerateEnemy(const Vector2& position, int enemyTier)
{
	Entity* entity = CreateGraphic(position, Vector2(TileWidth, TileHeight), NULL, Vector4(1, 1, 1, 1), 1);
	entity->Rename("Enemy");

	entity->AddComponent<BoxCollider>()->size.Set(TileWidth * 0.725f, TileHeight * 0.725f);
	entity->AddComponent<EnemyController>()->LateInit(enemyTier);

	entity->AttachChild(CreateGraphic(Vector2(0, 0), Vector2(TileWidth * 0.9f, TileHeight * 0.7f), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));

	Generate(scene->root, entity);
	return entity;
}

#include "Component\Script\StandardParticle.h"

Entity* EntityFactory::GenerateParticle(const Vector2& position, const Vector2& size, const char* animator, const char* animation, float alpha)
{
	Entity* entity = new Entity("Particle");
	entity->transform->SetPosition(position.x, position.y);
	entity->transform->SetSize(size.x, size.y);
	
	entity->AddComponent<SpriteRenderer>()->color.w = alpha;

	entity->AddComponent<SpriteAnimator>()->SetAnimator(Resource.GetAnimator(animator));
	entity->GetComponent<SpriteAnimator>()->Play(animation, false);
	
	entity->AddComponent<StandardParticle>();
		
	return Generate(scene->root, entity);
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
