#include "TowerGUI.h"
#include "TowerController.h"

#include "../../Entity.h"
#include "../TextRenderer2D.h"

#include "../../../Tower/TowerData.h"

#include "Utility.h"

void TowerGUI::ShowInfo(const char* type, TowerData* tower)
{
	if (tower)
	{
		name->SetText(type);
		damage->SetText(ToString(tower->damage).c_str());
		range->SetText(ToString(tower->range).c_str());
	}
	else
	{
		name->SetText("");
		damage->SetText("");
		range->SetText("");
	}
}

#include "../GUI/Button.h"
#include "TowerManager.h"

void TowerGUI::Init(Entity * ent)
{
	manager = ent->GetComponent<TowerManager>();
}

void TowerGUI::Update(double dt)
{
	for (auto& b : button)
	{
		if (b.second->IsState(Button::STATE_CLICK))
		{
			manager->SetToPlace(b.first.c_str());
			break;
		}
	}

	if (upgrade->IsState())
		manager->UpgradeTower();
}

void TowerGUI::EnableUpgrades()
{
	upgrade->Enable();
}

void TowerGUI::DisableUpgrades()
{
	upgrade->Disable();
}

void TowerGUI::AddButton(const char * key, Button * button)
{
	this->button[key] = button;
}
