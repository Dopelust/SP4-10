#include "PageSystem.h"

#include "../../../Entity.h"

PageSystem::PageSystem() : current(0)
{
}

PageSystem::~PageSystem()
{
}
#include "../../Transform.h"
void PageSystem::Update(double dt)
{
	for (auto& page : pages)
	{
		page->SetActive(false);
	}

	GetPage()->SetActive(true);
}

void PageSystem::AddPage(Entity * page)
{
	pages.push_back(page);
}

Entity* PageSystem::GetPage()
{
	if (current >= 0 && current < (int)pages.size())
		return pages[current];

	return NULL;
}

int PageSystem::GetPageNo()
{
	return current;
}

void PageSystem::SetPage(int page)
{
	if (page >= 0 && page < (int)pages.size())
	{
		current = page;
	}
}

bool PageSystem::HasPreviousPage()
{
	return current > 0;
}

bool PageSystem::HasNextPage()
{
	return current < (int)pages.size() - 1;
}

void PageSystem::NextPage()
{
	if (HasNextPage())
	{
		++current;
	}
}

void PageSystem::PreviousPage()
{
	if (HasPreviousPage())
	{
		--current;
	}
}
