#include "StageGUI.h"

#include "../../Entity.h"
#include "StageManager.h"
#include "../TextRenderer2D.h"

#include "Utility.h"

StageGUI::StageGUI()
{
}

StageGUI::~StageGUI()
{
}

#include "../../../../Screen.h"
#include "../../EntityFactory.h"
#include "../../../../GridInfo.h"
#include "Vector2.h"

void StageGUI::Init(Entity * ent)
{
	stage = ent->GetComponent<StageManager>();

	{
		Entity* entity = EntityFactory::GenerateTextGUI(Vector2(8, TileHeight * 0.5f), "", 200);
		timer = entity->GetComponent<TextRenderer2D>();
		timer->SetAlignCenter(false);
	}
	{
		Entity* entity = EntityFactory::GenerateTextGUI(Vector2(8, Screen.GetProjectionHeight() - TileHeight * 0.5f), "", 200);
		wave = entity->GetComponent<TextRenderer2D>();
		wave->SetAlignCenter(false);
	}
}

void StageGUI::Update(double dt)
{
	wave->SetText(ToString("Wave ", stage->currentWave).c_str());
	timer->SetText(ToString("Time: ", (int)(stage->waveTimer + 0.5f)).c_str());
}
