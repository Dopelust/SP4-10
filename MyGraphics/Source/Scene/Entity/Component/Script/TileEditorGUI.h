#pragma once

#include "../Component.h"

#include <vector>
using namespace::std;
class Transform;
class TileEditor;
class Button;

class TileEditorGUI : public Component
{
public:
	TileEditorGUI();
	~TileEditorGUI();

	Entity* select;

	void Init(Entity* ent);
	void Update(double dt);

	void AddButton(Button* button);

private:
	vector<Button*> button;
	void SetSelectedTile(int index);

	TileEditor* editor;
};