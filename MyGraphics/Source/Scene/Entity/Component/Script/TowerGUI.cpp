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
		damage->SetText(ToString(tower->pierce + 1).c_str());
		range->SetText(ToString(tower->range).c_str());
		force->SetText(ToString(tower->speed).c_str());
		speed->SetText(ToString(1.0f / tower->cooldown).c_str());
		projectiles->SetText(ToString(tower->shot).c_str());

		this->rank->SetActive(true);
		this->rank->SetSprite(Resource.GetSpritesheet("Rank")->GetSprite(rank));

		if (rank == TowerDatabase::GetMaxUpgrade(type))
			cost->SetText("");
		else
		{
			tower = &TowerDatabase::GetData(type)[rank + 1];
			cost->SetText(ToString('$', tower->cost).c_str());
		}

		sellprice->SetText(ToString('$', TowerDatabase::GetSellPrice(type, rank)).c_str());
	}
	else
	{
		name->SetText("");
		damage->SetText("");
		range->SetText("");
		force->SetText("");
		speed->SetText("");
		projectiles->SetText("");
		cost->SetText("");
		sellprice->SetText("");

		this->rank->SetActive(false);
	}
}

void TowerGUI::Init(Entity * ent)
{
	manager = ent->GetComponent<TowerManager>();
}

#include "../../../../InputHandler.h"
#include "HoverText.h"

void TowerGUI::Update(double dt)
{
	hover->owner->SetActive(false);

	for (auto& b : button)
	{
		if (b.second->IsHover())
		{
			hover->SetText(b.first.c_str());
			hover->owner->SetActive(true);
		}

		if (manager->CanPurchase(b.first.c_str()))
		{
			b.second->Enable();
			b.second->SetColor(0.85f, 0.85f, 0.85f, 1);
		}
		else
		{
			b.second->Disable();
			b.second->SetColor(0.85f, 0, 0, 1);
		}
	}

	for (auto& b : button)
	{
		if (b.second->IsState(Button::STATE_CLICK) || b.second->IsState(Button::STATE_PRESS))
		{
			manager->SetToPlace(b.first.c_str());
			break;
		}
	}

	if (manager->CanUpgrade())
	{
		EnableUpgrades();

		if (upgrade->IsState())
			manager->UpgradeTower();
	}
	else
		DisableUpgrades();

	if (sell->IsState())
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
	this->button[key]->SetKey(GLFW_KEY_0 + this->button.size());
}
