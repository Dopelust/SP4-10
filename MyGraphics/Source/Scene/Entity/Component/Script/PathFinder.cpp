#include "PathFinder.h"

#include "../../../AStar/AStar.h"

PathFinder::PathFinder() :
aStar(NULL),
start(NULL)
{
	aStar = new AStar();
}

PathFinder::~PathFinder()
{
	delete aStar;
	aStar = NULL;
}

void PathFinder::Init(Entity* ent)
{

}

void PathFinder::Update(double dt)
{

}

void PathFinder::Set(Vector2 start, Vector2 end)
{
	this->start = start;
	this->end = end;
}

void PathFinder::SetStart(Vector2 start)
{
	this->start = start;
}

void PathFinder::SetEnd(Vector2 end)
{
	this->end = end;
}

#include <map>

bool PathFinder::UpdateMap(vector<vector<bool>>& tileMap, const vector<Vector2> &endPoints)
{
	aStar->Update(tileMap);

	static map<float, Vector2> hMap;
	hMap.clear();

	for (auto& pt : endPoints)
	{
		hMap[aStar->Compute_h(start, pt)] = pt;
	}

	for (auto& h : hMap)
	{
		SetEnd(h.second);

		if (CalculatePath())
			return true;
	}

	return false;
}

bool PathFinder::CalculatePath()
{
	if (aStar->GetPath(start, end))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int PathFinder::GetPathLength()
{
	return aStar->GetPathLength();
}

Node* PathFinder::GetStart()
{
	return aStar->start;
}