#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "../Component.h"

#include <vector>

using std::vector;

#include "Vector2.h"

class AStar;
class Node;
class PathFinder :
	public Component
{
public:
	PathFinder();
	~PathFinder();

	void Init(Entity* ent);
	void Update(double dt);

	void Set(Vector2 start, Vector2 end);
	void SetStart(Vector2 start);
	void SetEnd(Vector2 end);
	void UpdateMap(vector<vector<bool>> &tileMap);
	bool CalculatePath();
	int GetPathLength();
	Node* GetStart();

private:
	AStar* aStar;

	// Indexes on grid
	Vector2 start;
	Vector2 end;
};

#endif