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

void TileEditorGUI::Init(Entity* entity)
{
	editor = entity->GetComponent<TileEditor>();

	editor->graphic->SetTexture(Resource.GetTexture("Tileset"));
	SetSelectedTile(0);
}

void TileEditorGUI::Update(double dt)
{
	for (int i = 0; i < button.size(); ++i)
	{
		if (button[i]->IsState(Button::STATE_CLICK))
		{
			SetSelectedTile(i);
			break;
		}
	}
}

void TileEditorGUI::AddButton(Button * button)
{
	this->button.push_back(button);
}

void TileEditorGUI::SetSelectedTile(int index)
{
	editor->index = index;

	Vector4& uv = Resource.GetSpritesheet("Tileset")->GetSprite(index)->GetUV();
	editor->graphic->SetUV(uv.x, uv.y, uv.z, uv.w);

	if (select)
		select->transform->Position() = button[index]->transform->Position();
}
