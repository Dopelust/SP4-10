#pragma once

#include "../Component.h"

#include <vector>
using namespace::std;

class Button;
class Popup : public Component
{
public:
	Popup();
	~Popup();

	const vector<Button*>& GetButtonList();
	void AddButton(Button* button);
	
	void PopUp();
	void Close();

	void Init(Entity* ent);
	void Update(double dt);
private:
	Entity* owner;
	vector<Button*> button;
};