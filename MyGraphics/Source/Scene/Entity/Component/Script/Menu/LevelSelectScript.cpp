#include "LevelSelectScript.h"

LevelSelectScript::LevelSelectScript()
{
}

LevelSelectScript::~LevelSelectScript()
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

void LevelSelectScript::Init(Entity * ent)
{
	int level = 1;

	vector<string>& line = File.GetLines("Data//Save//unlocked.txt");

	if (!line.empty())
		level = stoi(line[0]);

	AddLevel("Level 1", "level1", Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.33f, 525), ent, level < 1);
	AddLevel("Level 2", "level2", Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.66f, 525), ent, level < 2);
	AddLevel("Level 3", "level3", Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.33f, 265), ent, level < 3);
	AddLevel("Level 4", "level4", Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.66f, 265), ent, level < 4);
}

#include "MenuHandler.h"
#include "MenuScript.h"

void LevelSelectScript::Update(double dt)
{
	for (auto& level : levels)
	{
		if (level.second->IsState())
			PlayLevel(level.first.c_str());
	}
}

#define size Vector2(21 * 16, 13 * 16)
#define stroke Vector2(6, 6)

void LevelSelectScript::AddLevel(const char * name, const char * level, const Vector2 & position, Entity* owner, bool lock)
{
	Entity* entity = LevelSelectObject::AddLevel(name, level, position, owner);

	levels[level] = entity->AddComponent<Button>();
	levels[level]->SetGraphic(entity->GetComponent<CSVRenderer>());

	if (lock)
		levels[level]->Disable();
}
