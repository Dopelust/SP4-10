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

#include "Component\GUI\Popup.h"
#include "Component\Script\StandardPopup.h"

Entity * EntityFactory::GeneratePopup(const Vector2 & size, const char* text, float textsize)
{
	Entity* entity = GenerateGraphic(Vector2(scene->GetResolutionX(scene->canvas) * 0.5f, scene->GetResolutionY(scene->canvas) * 0.5f),
		size, NULL, Vector4(0.7f, 0.7f, 0.7f));

	entity->AttachChild(CreateGraphic(Vector2(0, (size.y - size.y * 0.75f) * 0.5f), Vector2(size.x * 0.9f, size.y * 0.75f), NULL, Vector4(0.75f, 0.75f, 0.75f)));
	entity->AttachChild(CreateGraphic(Vector2(0, size.y * 0.5f), Vector2(size.x, 32), NULL,
		Vector4(0.1f, 0.1f, 0.1f)));

	entity->AddComponent<Popup>();
	entity->AddComponent<StandardPopup>()->text =
		entity->AttachChild(CreateTextGUI(Vector2(0, size.y * 0.125f), text, textsize))->GetComponent<TextRenderer2D>();

	Entity* child = entity->AttachChild(CreateGraphic(Vector2(size.x * 0.3375f, -size.y * 0.375f), Vector2(64 + 4, 20 + 4), NULL, Vector3(0.3f, 0.3f, 0.3f)));
	child->AttachChild(CreateTextGUI(Vector2(), "Cancel", 128));
	Button* button = child->AttachChild(CreateButton(Vector2(), Vector2(64, 20), NULL, Vector3(0.7f, 0.7f, 0.7f), true))->GetComponent<Button>();
	entity->GetComponent<Popup>()->AddButton(button);
	entity->GetComponent<StandardPopup>()->cancel = button;

	child = entity->AttachChild(CreateGraphic(Vector2(size.x * 0.3375f - 68 - 8, -size.y * 0.375f), Vector2(64 + 4, 20 + 4), NULL, Vector3(0.3f, 0.3f, 0.3f)));
	child->AttachChild(CreateTextGUI(Vector2(), "OK", 128));
	button = child->AttachChild(CreateButton(Vector2(), Vector2(64, 20), NULL, Vector3(0.7f, 0.7f, 0.7f), true))->GetComponent<Button>();
	entity->GetComponent<Popup>()->AddButton(button);
	entity->GetComponent<StandardPopup>()->ok = button;

	child = entity->AttachChild(CreateGraphic(Vector2(size.x * 0.5f - 13 - 3, size.y * 0.5f), Vector2(22 + 4, 22 + 4), NULL, Vector3(0.3f, 0.3f, 0.3f)));
	child->AttachChild(CreateTextGUI(Vector2(), "X", 128));
	button = child->AttachChild(CreateButton(Vector2(), Vector2(22, 22), NULL, Vector3(0.7f, 0, 0), true))->GetComponent<Button>();
	entity->GetComponent<Popup>()->AddButton(button);
	entity->GetComponent<StandardPopup>()->close = button;
	
	entity->SetActive(false);
	return entity;
}

Entity * EntityFactory::GenerateTextButton(const Vector2 & position, const char * text, float size, const Vector3 & color)
{
	return Generate(scene->canvas, CreateTextButton(position, text, size, color));
}

Entity * EntityFactory::GenerateButton(const Vector2 & position, const Vector2 & size, Texture * texture, const Vector3& color, bool gloss)
{
	return Generate(scene->canvas, CreateButton(position, size, texture, color, gloss));
}

Entity* EntityFactory::GenerateSlider(const Vector2 & position, const Vector2 & size, const char* tag, Texture * texture, float min, float value, float max,bool integer)
{
	return Generate(scene->canvas, CreateSlider(position,size,tag,min,value,max,integer));
}

#include "../../FontManager.h"
#include "../../Font.h"

Entity* EntityFactory::GenerateInputField(const Vector2& position, const Vector3& color, int limit, float textSize)
{
	return Generate(scene->canvas, CreateInputField(position, color, limit, textSize));
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

	Entity* fill = entity->AttachChild(CreateGraphic(Vector2(), size, NULL, Vector3(0.9f, 0.9f, 0)));

	Entity* slider = entity->AttachChild(CreateButton(Vector2(), Vector2(8, size.y), NULL, Vector3(0, 0, 0)));
	slider->Rename("Slider");
	slider->AddComponent<Slider>()->guide = guide->GetComponent<Button>();
	slider->GetComponent<Slider>()->fill = fill->transform;

	Entity* text = entity->AttachChild(CreateTextGUI(Vector2(-size.x *0.5f, 24), tag, 256));
	text->GetComponent<TextRenderer2D>()->SetAlignCenter(false);

	text = entity->AttachChild(CreateTextGUI(Vector2(size.x * 0.5f + 16, 0), "", 200));
	text->GetComponent<TextRenderer2D>()->SetAlignCenter(false);

	if (!integer)
		slider->GetComponent<Slider>()->valueType = Slider::SLIDER_FLOAT;

	slider->GetComponent<Slider>()->SetText(text->GetComponent<TextRenderer2D>());
	slider->GetComponent<Slider>()->SetMin(min);
	slider->GetComponent<Slider>()->SetMax(max);
	slider->GetComponent<Slider>()->SetValue(value);

	slider = slider->AttachChild(CreateGraphic(Vector2(), Vector2(4, size.y), NULL, Vector3(1, 1, 1)));

	return entity;
}

Entity * EntityFactory::CreateCheckbox(const Vector2 & position, float size, float stroke, const char * text)
{
	Entity* entity = CreateGraphic(position, Vector2(size + stroke, size + stroke), NULL, Vector3(0.9f, 0.9f, 0.9f));

	Entity* t = CreateTextGUI(Vector2(size, 0), text, size * 8);
	t->GetComponent<TextRenderer2D>()->SetAlignCenter(false);

	entity->AttachChild(t);

	Entity* button = entity->AttachChild(CreateButton(Vector2(), Vector2(size, size), NULL, Vector3(0.2f, 0.2f, 0.2f)));
	button->AddComponent<Toggle>();

	button->AddComponent<Checkbox>()->check = button->AttachChild(CreateGraphic(Vector2(), Vector2(size * 0.5f, size * 0.5f), NULL, Vector3(0.9f, 0.9f, 0.9f)));
	button->GetComponent<Checkbox>()->check->Rename("Check");

	return entity;
}

Entity * EntityFactory::CreateInputField(const Vector2 & position, const Vector3 & color, int limit, float textSize)
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

#include "Component\Script\CSVRenderer.h"

Entity * EntityFactory::CreateCSVGraphic(const Vector2 & position, const Vector2 & size, const char * filepath, const Vector4 & color, int layer)
{
	Entity* entity = new Entity("Graphic");
	entity->transform->SetPosition(position.x, position.y);
	entity->transform->SetSize(size.x, size.y);

	entity->AddComponent<CSVRenderer>()->UploadCSV(filepath);
	entity->GetComponent<CSVRenderer>()->SetSpritesheet(Resource.GetSpritesheet("Tileset"));
	entity->GetComponent<CSVRenderer>()->SetLayer(layer);
	entity->GetComponent<CSVRenderer>()->color = color;

	return entity;
}

Entity * EntityFactory::CreateGraphic(const Vector2 & position, const Vector2 & size, Texture * texture, const Vector4 & color, int layer)
{
	Entity* entity = new Entity("Graphic");
	entity->transform->SetPosition(position.x, position.y);
	entity->transform->SetSize(size.x, size.y);

	entity->AddComponent<Graphic2D>()->texture = texture;
	entity->GetComponent<Graphic2D>()->color = color;
	entity->GetComponent<Graphic2D>()->SetLayer(layer);
	
	return entity;
}

Entity * EntityFactory::CreateButton(const Vector2 & position, const Vector2 & size, Texture * texture, const Vector3 & color, bool gloss)
{
	Entity* entity = CreateGraphic(position, size, texture, color);
	entity->AddComponent<Button>();

	entity->Rename("Button");

	if (gloss)
	{
		entity->AttachChild(CreateGraphic(Vector2(0, size.y * 0.3f), Vector2(size.x, size.y * 0.4f), NULL, Vector4(1, 1, 1, 0.2f), 1));
	}

	return entity;
}

Entity * EntityFactory::CreateTextButton(const Vector2 & position, const char * text, float size, const Vector3 & color)
{
	Entity* entity = CreateButton(position, FontManager::Instance().GetFont()->GetTextSize(text) * size, NULL, color);

	TextRenderer2D* t = entity->AttachChild(CreateTextGUI(Vector2(), text, size))->GetComponent<TextRenderer2D>();
	t->color = color;

	entity->GetComponent<Button>()->SetGraphic(t);
	entity->GetComponent<Graphic2D>()->SetActive(false);

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

	if (type == "bubble_blower")
	{
		entity->GetComponent<Graphic2D>()->texture = Resource.GetTexture("Bubble Blower");
		entity->transform->Size() *= 1.75f;

		entity->AttachChild(CreateGraphic(Vector2(), Vector2(TileWidth * 1.3f, TileHeight * 1.3f), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));
	}
	else if (type == "sniper")
	{
		entity->GetComponent<Graphic2D>()->texture = (Resource.GetTexture("Sniper"));
		entity->transform->Size() *= 2.5f;

		entity->AttachChild(CreateGraphic(Vector2(), Vector2(TileWidth * 1.3f, TileHeight * 1.3f), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));
	}
	else if (type == "fountain")
	{
		entity->GetComponent<Graphic2D>()->texture = (Resource.GetTexture("Fountain"));
		entity->transform->Size() *= 1.1f;

		entity->AttachChild(CreateGraphic(Vector2(), Vector2(TileWidth * 1.1f, TileHeight * 1.1f), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));
	}
	else if (type == "dispenser")
	{
		entity->GetComponent<Graphic2D>()->texture = (Resource.GetTexture("Dispenser"));
		entity->transform->Size() *= 1.75f;

		entity->AttachChild(CreateGraphic(Vector2(), Vector2(TileWidth * 0.8f, TileHeight * 0.8f), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));
	}
	else if (type == "bubble_cannon")
	{
		entity->GetComponent<Graphic2D>()->texture = (Resource.GetTexture("Bomber"));
		entity->transform->Size() *= 1.5f;

		entity->AttachChild(CreateGraphic(Vector2(), Vector2(TileWidth * 0.8f, TileHeight * 0.8f), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));
	}
	else if (type == "glue_gun")
	{
		entity->GetComponent<Graphic2D>()->texture = (Resource.GetTexture("Turret"));
		entity->transform->Size() *= 2.5f;

		entity->AttachChild(CreateGraphic(Vector2(), Vector2(TileWidth, TileHeight), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));
	}

	Entity* child = entity->AttachChild(CreateSprite(Vector2(TileWidth * 0.5f - 6, TileHeight * -0.5f + 8), Vector2(16, 16), Resource.GetSpritesheet("Rank")->GetSprite(0), Vector4(1, 1, 1, 1), 4));
	entity->GetComponent<TowerController>()->rank = child->GetComponent<SpriteRenderer>();

	Generate(scene->root, entity);
	return entity;
}

#include "Component\Script\ProjectileController.h"

Entity* EntityFactory::GenerateProjectile(const Vector2& position, string type)
{
	Entity* entity = NULL;

	if (type == "Bubble")
	{
		entity = CreateGraphic(position, Vector2(TileWidth * 0.5f, TileHeight * 0.5f), Resource.GetTexture(type.c_str()), Vector4(1, 1, 1, 1), 7);
		entity->AddComponent<BoxCollider>()->size = Vector3(TileWidth * 0.4f, TileHeight * 0.4f, 0);
	}
	else if (type == "Glue")
	{
		entity = CreateGraphic(position, Vector2(TileWidth * 0.9f, TileHeight * 0.9f), Resource.GetTexture("Water"), Vector4(5, 5, 5, 0.5f), 7);
		entity->AddComponent<BoxCollider>()->size = Vector3(TileWidth * 0.2f, TileHeight * 0.2f, 0);
	}
	else
	{
		entity = CreateGraphic(position, Vector2(TileWidth * 0.9f, TileHeight * 0.9f), Resource.GetTexture(type.c_str()), Vector4(1, 1, 1, 1), 7);
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

Entity* EntityFactory::GenerateEnemy(const Vector2& position, int enemyTier, const char* animator, const char* animation, const bool flying)
{
	Entity* entity = new Entity("Enemy");//CreateGraphic(position, Vector2(TileWidth, TileHeight), NULL, Vector4(1, 1, 1, 1), 1);
	//entity->Rename("Enemy");
	entity->transform->SetPosition(position.x, position.y);
	entity->transform->SetSize(TileWidth, TileHeight);

	entity->AddComponent<SpriteRenderer>()->SetLayer(1);
	entity->AddComponent<SpriteAnimator>()->SetAnimator(Resource.GetAnimator(animator));
	entity->GetComponent<SpriteAnimator>()->Play(animation, true);

	entity->AddComponent<BoxCollider>()->size.Set(TileWidth * 0.725f, TileHeight * 0.725f);
	entity->AddComponent<EnemyController>()->Init(enemyTier);
	entity->GetComponent<EnemyController>()->LateInit(flying);

	if (flying)
	{
		Entity* wings = new Entity("Enemy Wings");
		wings->transform->SetPosition(0, 4);
		wings->transform->SetSize(TileWidth * 1.75f, TileHeight * 1.75f);
		wings->AddComponent<SpriteRenderer>()->SetLayer(4);
		entity->GetComponent<SpriteRenderer>()->SetLayer(5);
		wings->AddComponent<SpriteAnimator>()->SetAnimator(Resource.GetAnimator("Wings"));
		wings->GetComponent<SpriteAnimator>()->Play("Wings", true);

		entity->AttachChild(wings);
	}

	entity->AttachChild(CreateGraphic(Vector2(0, -1), Vector2(TileWidth * 0.85f, TileHeight * 0.65f), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));

	Generate(scene->root, entity);
	return entity;
}

Entity* EntityFactory::CreateSpriteAnimation(const Vector2& position, const Vector2& size, const char * animator, const char * animation, const Vector4 &color, int layer, bool play, bool occlusion)
{
	Entity* entity = new Entity();
	entity->transform->SetPosition(position.x, position.y);
	entity->transform->SetSize(size.x, size.y);

	entity->AddComponent<SpriteRenderer>()->SetLayer(layer);
	entity->GetComponent<SpriteRenderer>()->color = color;
	entity->AddComponent<SpriteAnimator>()->SetAnimator(Resource.GetAnimator(animator));
	entity->GetComponent<SpriteAnimator>()->Play(animation, play);

	if (occlusion)
		entity->AttachChild(CreateGraphic(Vector2(0, -1), Vector2(TileWidth * 0.85f, TileHeight * 0.65f), Resource.GetTexture("Occlusion"), Vector4(1, 1, 1, 1)));

	return entity;
}

#include "Component\Script\StandardParticle.h"

Entity * EntityFactory::CreateParticle(const Vector2 & position, const Vector2 & size, const char * animator, const char * animation, float alpha)
{
	Entity* entity = new Entity("Particle");
	entity->transform->SetPosition(position.x, position.y);
	entity->transform->SetSize(size.x, size.y);

	entity->AddComponent<SpriteRenderer>()->color.w = alpha;
	entity->GetComponent<SpriteRenderer>()->SetLayer(6);

	entity->AddComponent<SpriteAnimator>()->SetAnimator(Resource.GetAnimator(animator));
	entity->GetComponent<SpriteAnimator>()->Play(animation, false);

	entity->AddComponent<StandardParticle>();

	return entity;
}

Entity* EntityFactory::GenerateParticle(const Vector2& position, const Vector2& size, const char* animator, const char* animation, float alpha)
{
	return Generate(scene->root, CreateParticle(position, size, animator, animation, alpha));
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
