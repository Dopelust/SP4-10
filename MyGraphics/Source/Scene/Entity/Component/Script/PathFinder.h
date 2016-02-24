#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "../Component.h"

#include <vector>
using std::vector;

#include "Vector2.h"
#include "../../../AStar/Path.h"

class PathFinder : public Component
{
public:
	PathFinder();
	~PathFinder();

	void Init(Entity* ent);
	void Update(double dt);

	bool UpdateMap(vector<vector<bool>> &tileMap, const Vector2& start, const vector<Vector2> &endPoints);
	bool UpdateMap(vector<vector<bool>> &tileMap, const Vector2& start, const Vector2& end);

	bool CalculatePath(const Vector2& start, const Vector2& end);

	Vector2 GetTarget();
	bool Traverse();
	bool IsEndOfPath();
	bool HasPath();

private:
	Path path;
	int index;
};

#endif