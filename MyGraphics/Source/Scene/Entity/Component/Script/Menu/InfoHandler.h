#pragma once

#include "StateObject.h"

class PageSystem;
class Button;

class InfoHandler : public StateObject
{
public:
	InfoHandler();
	~InfoHandler();

	void Init(Entity* ent);
	void Update(double dt);

private:
	PageSystem* page;

	Button* next;
	Button* prev;

	Button* back;
};