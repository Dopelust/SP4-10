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
		Entity* entity = EntityFactory::GenerateTextGUI(Vector2(Screen.GetProjectionWidth() * 0.5f, Screen.GetProjectionHeight() * 0.5f), "", 400);
		popup = entity->GetComponent<TextRenderer2D>();
		popup->color.w = 0;
	}
	{
		Entity* entity = EntityFactory::GenerateTextGUI(Vector2(140, TileHeight * 0.5f), "", 200);
		timer = entity->GetComponent<TextRenderer2D>();
		timer->SetAlignCenter(false);
	}
	{
		Entity* entity = EntityFactory::GenerateTextGUI(Vector2(8, Screen.GetProjectionHeight() - TileHeight * 0.5f), "", 200);
		wave = entity->GetComponent<TextRenderer2D>();
		wave->SetAlignCenter(false);
	}
	{
		Entity* entity = EntityFactory::GenerateTextGUI(Vector2(160, Screen.GetProjectionHeight() - TileHeight * 0.5f), "", 200);
		health = entity->GetComponent<TextRenderer2D>();
		health->color.Set(1, 0, 0);
		health->SetAlignCenter(false);
	}
	{
		Entity* entity = EntityFactory::GenerateTextGUI(Vector2(270, Screen.GetProjectionHeight() - TileHeight * 0.5f), "", 200);
		gold = entity->GetComponent<TextRenderer2D>();
		gold->color.Set(1, 1, 0);
		gold->SetAlignCenter(false);
	}
	{
		Entity* entity = EntityFactory::GenerateButton(Vector2(64, TileHeight * 0.5f), Vector2(128, TileHeight), NULL, Vector3(0.6f, 0.6f, 0.6f));
		pause = entity->GetComponent<Button>();
		pauseText = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "START", 200))->GetComponent<TextRenderer2D>();
	}
}

void StageGUI::Update(double dt)
{
	wave->SetText(ToString("Wave ", stage->currentWave + 1).c_str());
	timer->SetText(ToString("Time: ", (int)(stage->waveTimer + 0.5f)).c_str());
	health->SetText(ToString(stage->health, "HP").c_str());
	gold->SetText(ToString("$", stage->gold).c_str());

	switch (stage->state)
	{
	case StageManager::FREETIME:
		pauseText->SetText("START");
		break;
	case StageManager::WAVE:
		pauseText->SetText("PAUSE");
		break;
	case StageManager::PAUSED:
		pauseText->SetText("RESUME");
		break;
	}

	Fall(popup->color.w, dt * 0.75f, 0);
}

#include "../GUI/Button.h"

bool StageGUI::ButtonPress()
{
	return pause->IsState();
}

void StageGUI::SetPopup(const char * text)
{
	popup->SetText(text);
	popup->color.w = 1;
}
