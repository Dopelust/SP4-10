#include "TowerInfoGUI.h"
#include "TowerController.h"

#include "../../Entity.h"
#include "../TextRenderer2D.h"

#include "../../../Tower/TowerData.h"

#include "Utility.h"

void TowerInfoGUI::ShowInfo(TowerData* tower)
{
	if (tower)
	{
		range->SetText(ToString(tower->range).c_str());
	}
	else
	{
		range->SetText("");
	}
}