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

void PathFinder::UpdateMap(vector<vector<bool>>& tileMap)
{
	aStar->Update(tileMap);
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
	return aStar->GetStartNode();
}