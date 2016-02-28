#include "LevelSelectObject.h"

LevelSelectObject::LevelSelectObject()
{
}

LevelSelectObject::~LevelSelectObject()
{
}

#include "../../../../Scene.h"
#include "../../../Entity.h"
#include "../../../EntityFactory.h"
#include "../../Transform.h"

#include "../../GUI/Button.h"
#include "../../GUI/Slider.h"

#include "Vector2.h"
#include "../CSVRenderer.h"
#include "../../TextRenderer2D.h"

#include "FileSystem.h"
#include "Utility.h"

#define size Vector2(21 * 16, 13 * 16)
#define stroke Vector2(6, 6)

Entity* LevelSelectObject::AddLevel(const char * name, const char * level, const Vector2 & position, Entity* owner)
{
	Entity* entity = owner->AttachChild(EntityFactory::CreateGraphic(position, size + stroke, NULL, Vector4(0, 0, 0)));
	entity->AttachChild(EntityFactory::CreateGraphic(Vector2(0, size.y * 0.3f), Vector2(size.x, size.y * 0.4f), NULL, Vector4(1, 1, 1, 0.1f), 1));

	entity = entity->AttachChild(EntityFactory::CreateCSVGraphic(Vector2(), size, ToString("Data//Levels//", level, ".csv").c_str(), Vector4(1, 1, 1)));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, size.y * 0.5f), name, 300))
		->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

	return entity;
}

#include "../../../../../GameEngine.h"
#include "../../../../../PlayState.h"

void LevelSelectObject::PlayLevel(const char * level)
{
	File.Remove("Data//Save//stats.txt");
	File.Remove("Data//Save//save.txt");

	PlayState::Instance().level = level;
	Engine.ChangeState(&PlayState::Instance());
}
