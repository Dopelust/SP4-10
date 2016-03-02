#include "StageGUI.h"

#include "../../Entity.h"
#include "StageManager.h"
#include "../TextRenderer2D.h"

#include "Utility.h"

StageGUI::StageGUI() : popup(NULL)
{
}

StageGUI::~StageGUI()
{
}

#include "../../../../Screen.h"
#include "../GUI/Popup.h"
#include "SimplePopup.h"

#include "../../EntityFactory.h"
#include "../../../../GridInfo.h"
#include "Vector2.h"
#include "../GUI/Button.h"

void StageGUI::EndStage(bool win)
{
	if (!popup)
	{
		popup = EntityFactory::GenerateTextButton(Vector2(GridWidth, Screen.GetProjectionHeight()) * 0.5f,
			"> Return to Main Menu <", 300, Vector3(0.9f, 0.9f, 0.9f));

		if (win)
		{
			popup->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, 96),
				"You Win!", 800))->GetComponent<TextRenderer2D>()->color.Set(1, 1, 0);
		}
		else
		{
			popup->AttachChild(EntityFactory::CreateTextGUI(Vector2(0, 96),
				"You Lost...", 800))->GetComponent<TextRenderer2D>()->color.Set(1, 0, 0);
		}

		popup->AddComponent<Popup>()->AddButton(popup->GetComponent<Button>());
		popup->GetComponent<Popup>()->PopUp();
	}
}

void StageGUI::Init(Entity * ent)
{
	stage = ent->GetComponent<StageManager>();

	{
		Entity* entity = EntityFactory::GenerateTextGUI(Vector2(GridWidth * 0.5f, Screen.GetProjectionHeight() * 0.55f), "", 400);
		indicator = entity->GetComponent<TextRenderer2D>();
		indicator->color.w = 0;
	}
	{
		Entity* entity = EntityFactory::GenerateTextGUI(Vector2(140, TileHeight * 0.5f), "", 200);
		timer = entity->GetComponent<TextRenderer2D>();
		timer->SetAlignCenter(false);
	}
	{
		Entity* entity = EntityFactory::GenerateTextGUI(Vector2(16, Screen.GetProjectionHeight() - TileHeight * 0.5f), "", 256);
		wave = entity->GetComponent<TextRenderer2D>();
		wave->SetAlignCenter(false);
	}
	{
		Entity* entity = EntityFactory::GenerateTextGUI(Vector2(200, Screen.GetProjectionHeight() - TileHeight * 0.5f), "", 200);
		health = entity->GetComponent<TextRenderer2D>();
		health->color.Set(1, 0, 0);
		health->SetAlignCenter(false);
	}
	{
		Entity* entity = EntityFactory::GenerateTextGUI(Vector2(300, Screen.GetProjectionHeight() - TileHeight * 0.5f), "", 200);
		gold = entity->GetComponent<TextRenderer2D>();
		gold->color.Set(1, 1, 0);
		gold->SetAlignCenter(false);
	}
	{
		Entity* entity = EntityFactory::GenerateButton(Vector2(64, TileHeight * 0.5f), Vector2(128, TileHeight), NULL, Vector3(0.5f, 0.5f, 0.5f), true);
		pause = entity->GetComponent<Button>();
		pause->SetKey(' ');
		pause->text = entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "START", 200))->GetComponent<TextRenderer2D>();
	}
	{
		Entity* entity = EntityFactory::GenerateButton(Vector2(Screen.GetProjectionWidth() - TileWidth * 0.5f, Screen.GetProjectionHeight() - TileHeight * 0.5f), Vector2(TileWidth, TileHeight), NULL, Vector3(0.7f, 0, 0), true);
		entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "X", 300));
		quit = entity->GetComponent<Button>();

		quitPopup = EntityFactory::GeneratePopup(Vector2(300, 150), "", 150);
	}
}

#include "StandardPopup.h"
#include "../../../../Time.h"
#include "../../../../GameEngine.h"
#include "../../../../MenuState.h"

void StageGUI::Update(double dt)
{
	if (popup)
	{
		if (popup->GetComponent<Button>()->IsState())
			Engine.ChangeState(&MenuState::Instance());
	}

	wave->SetText(ToString("Wave ", stage->currentWave + 1).c_str());
	timer->SetText(ToString("Time: ", (int)(stage->waveTimer + 0.5f)).c_str());
	health->SetText(ToString(stage->health, "HP").c_str());
	gold->SetText(ToString(stage->gold, 'G').c_str());

	switch (stage->state)
	{
	case StageManager::FREETIME:
		pause->text->SetText("START");
		break;
	case StageManager::WAVE:
		pause->text->SetText("PAUSE");
		break;
	case StageManager::PAUSED:
		pause->text->SetText("RESUME");
		break;
	}

	Fall(indicator->color.w, Time.GetUnscaledTime() * 0.6f, 0);

	if (quit->IsState())
		quitPopup->GetComponent<StandardPopup>()->PopUp("Return to Main Menu?");

	if (quitPopup->IsActive() && quitPopup->GetComponent<StandardPopup>()->IsOK())
		Engine.ChangeState(&MenuState::Instance());
}

#include "../GUI/Button.h"
#include "../../../../InputHandler.h"

bool StageGUI::ButtonPress()
{
	return pause->IsState(Button::STATE_CLICK) || pause->IsState(Button::STATE_PRESS);
}

void StageGUI::SetPopup(const char * text)
{
	indicator->SetText(text);
	indicator->color.w = 1;
}
