#include "TowerGUI.h"
#include "TowerController.h"

#include "../../Entity.h"
#include "../TextRenderer2D.h"

#include "../../../Tower/TowerDatabase.h"
#include "../../../Tower/TowerData.h"

#include "../SpriteRenderer.h"

#include "Utility.h"

#include "../../../../Spritesheet.h"
#include "../../../../Assets.h"

#include "../GUI/Button.h"
#include "TowerManager.h"


void TowerGUI::ShowInfo(const char* type, int rank)
{
	if (string(type) != "")
	{
		TowerData* tower = &TowerDatabase::GetData(type)[rank];

		name->SetText(type);
		damage->SetText(ToString(tower->pierce).c_str());
		range->SetText(ToString(tower->range).c_str());

		this->rank->SetActive(true);
		this->rank->SetSprite(Resource.GetSpritesheet("Rank")->GetSprite(rank));

		if (rank == TowerDatabase::GetMaxUpgrade(type))
			cost->SetText("");
		else
		{
			tower = &TowerDatabase::GetData(type)[rank + 1];
			cost->SetText(ToString('$', tower->cost).c_str());
		}

		int price = 0;

		for (int i = 0; i <= rank; ++i)
		{
			tower = &TowerDatabase::GetData(type)[i];
			price += tower->cost * 0.5f;
		}

		sellprice->SetText(ToString('$', price).c_str());
	}
	else
	{
		name->SetText("");
		damage->SetText("");
		range->SetText("");
		cost->SetText("");
		sellprice->SetText("");

		this->rank->SetActive(false);
	}
}

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

	else if (sell->IsState())
		manager->SellTower();
}

void TowerGUI::EnableSale()
{
	sell->Enable();
}

void TowerGUI::DisableSale()
{
	sell->Disable();
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
