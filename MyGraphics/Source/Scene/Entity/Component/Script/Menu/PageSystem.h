#pragma once

#include "../../Component.h"

#include <vector>
using namespace::std;

class PageSystem : public Component
{
public:
	PageSystem();
	~PageSystem();

	virtual void Update(double dt);

	void AddPage(Entity* page);
	Entity* GetPage();
	int GetPageNo();
	void SetPage(int page);

	bool HasPreviousPage();
	bool HasNextPage();

	virtual void NextPage();
	virtual void PreviousPage();

private:
	vector<Entity*> pages;
	int current;
};