#include "TileEditor.h"
#include "TileEditorGUI.h"

#include "../Transform.h"
#include "../../Entity.h"
#include "../GUI/Button.h"
#include "../Graphic2D.h"

#include "../../../../Assets.h"
#include "../../../../Spritesheet.h"
#include "../../../../Sprite.h"

TileEditorGUI::TileEditorGUI() : select(NULL)
{
}

TileEditorGUI::~TileEditorGUI()
{
}

void TileEditorGUI::SetEditor(TileEditor * editor)
{
	this->editor = editor;
	SetSelectedTile(0);
}

void TileEditorGUI::Init(Entity* entity)
{
	
}

#include "HoverText.h"

void TileEditorGUI::Update(double dt)
{
	hover->owner->SetActive(false);

	for (int i = 0; i < button.size(); ++i)
	{
		if (button[i]->IsHover())
		{
			hover->owner->SetActive(true);

			switch (i)
			{
			case 0:
				hover->SetText("Floor"); break;
			case 1:
				hover->SetText("Hole"); break;
			case 2:
				hover->SetText("Wall"); break;
			case 3:
				hover->SetText("Entrance"); break;
			case 4:
				hover->SetText("Exit"); break;
			}

			break;
		}
	}


	for (int i = 0; i < button.size(); ++i)
	{
		if (button[i]->IsState(Button::STATE_CLICK) || button[i]->IsState(Button::STATE_PRESS))
		{
			SetSelectedTile(i);
			break;
		}
	}
}

void TileEditorGUI::AddButton(Button * button)
{
	this->button.push_back(button);
	button->SetKey('0' + this->button.size());
}

#include "../SpriteRenderer.h"

void TileEditorGUI::SetSelectedTile(int index)
{
	editor->index = index;
	editor->sprite->SetSprite(Resource.GetSpritesheet("Tileset")->GetSprite(index));

	if (select)
		select->transform->Position() = button[index]->transform->Position();
}
