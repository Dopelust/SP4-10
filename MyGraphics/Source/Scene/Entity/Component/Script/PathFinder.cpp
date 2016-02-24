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

	static map<float, Path> pathMap;
	pathMap.clear();

	for (auto& pt : endPoints)
	{
		Path& p = AStar::GetPath(start, pt);

		if (p.GetPathLength())
			pathMap[p.GetPathLength()] = p;
	}

	if (pathMap.empty())
		return false;

	path = pathMap.begin()->second;
	index = path.GetPathLength() - 1;
	return true;
}

bool PathFinder::UpdateMap(vector<vector<bool>>& tileMap, const Vector2 & start, const Vector2 & end)
{
	AStar::Update(tileMap);

	if (CalculatePath(start, end))
		return true;

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