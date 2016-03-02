#pragma once

#include "../Component.h"

#include <vector>
using namespace::std;
class Transform;
class TileEditor;
class Button;
class HoverText;

class TileEditorGUI : public Component
{
public:
	TileEditorGUI();
	~TileEditorGUI();

	HoverText* hover;
	Entity* select;

	void SetEditor(TileEditor* editor);
	void Init(Entity* ent);
	void Update(double dt);

	void AddButton(Button* button);

private:
	TileEditor* editor;
	vector<Button*> button;
	void SetSelectedTile(int index);
};