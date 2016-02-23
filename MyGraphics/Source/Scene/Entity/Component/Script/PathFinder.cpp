#include "PathFinder.h"

#include "../../../AStar/AStar.h"

PathFinder::PathFinder() : index(0)
{
}

PathFinder::~PathFinder()
{
}

void PathFinder::Init(Entity* ent)
{

}

void PathFinder::Update(double dt)
{

}

//void PathFinder::Set(Vector2 start, Vector2 end)
//{
//	this->start = start;
//	this->end = end;
//}
//
//void PathFinder::SetStart(Vector2 start)
//{
//	this->start = start;
//}
//
//void PathFinder::SetEnd(Vector2 end)
//{
//	this->end = end;
//}

#include <map>

bool PathFinder::UpdateMap(vector<vector<bool>>& tileMap, const Vector2& start, const vector<Vector2> &endPoints)
{
	AStar::Update(tileMap);

	static map<float, Vector2> hMap;
	hMap.clear();

	for (auto& pt : endPoints)
	{
		hMap[pt.DistSquared(start)] = pt;
	}

	for (auto& h : hMap)
	{
		if (CalculatePath(start, h.second))
			return true;
	}

	return false;
}

bool PathFinder::CalculatePath(const Vector2& start, const Vector2& end)
{
	path = AStar::GetPath(start, end);

	if (path.GetPathLength())
	{
		index = path.GetPathLength() - 1;
		return true;
	}
	
	return false;
}

Vector2 PathFinder::GetTarget()
{
	return path.GetPath(index);
}

bool PathFinder::Traverse()
{
	if (index > 0)
	{
		--index;
		return true;
	}

	return false;
}

bool PathFinder::IsEndOfPath()
{
	return index == 0;
}

bool PathFinder::HasPath()
{
	return path.GetPathLength();
}

//int PathFinder::GetPathLength()
//{
//	return aStar->GetPathLength();
//}
//
//Node* PathFinder::GetStart()
//{
//	return aStar->start;
//}