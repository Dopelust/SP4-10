#include "TowerPlacer.h"
#include "TowerPlacerGUI.h"

#include "Vector2.h"
#include "../../../../InputHandler.h"
#include "../../../../Grid.h"
#include "../../../../Tile.h"

#include "../../../Scene.h"
#include "../Transform.h"
#include "../../Entity.h"
#include "../GUI/Button.h"

TowerPlacerGUI::TowerPlacerGUI()
{
}

TowerPlacerGUI::~TowerPlacerGUI()
{
}

void TowerPlacerGUI::Init(Entity* entity)
{
	placer = entity->GetComponent<TowerPlacer>();
}

#include "../../../Tower/TowerDatabase.h"
#include "../Graphic2D.h"
#include "../../../../Assets.h"

void TowerPlacerGUI::Update(double dt)
{
	for (auto& b : button)
	{
		if (b.second->IsState(Button::STATE_CLICK))
		{
			placer->type = b.first;
			placer->ShowInfo(&TowerDatabase::GetData(placer->type.c_str())["INITIAL"]);

			placer->graphic->SetTexture(Resource.GetTexture("Archer"));
			placer->transform->SetSize(TileWidth * 1.75f, TileHeight * 1.75f);

			break;
		}
	}
}

void TowerPlacerGUI::AddButton(const char * key, Button * button)
{
	this->button[key] = button;
}
