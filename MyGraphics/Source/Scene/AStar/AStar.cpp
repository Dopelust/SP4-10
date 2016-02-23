#include "AStar.h"
#include "ASnode.h"
#include <queue>

static int dx[AStar::dir] = { 1, 0, -1, 0 };
static int dy[AStar::dir] = { 0, 1, 0, -1 };

int AStar::row = 0;
int AStar::col = 0;

vector<vector<bool>> AStar::tileMap;
vector<vector<bool>> AStar::openMap;
vector<vector<bool>> AStar::closeMap;
vector<vector<int>> AStar::dirMap;

// Determine priority (in the priority queue)
bool operator<(const ASnode & a, const ASnode & b)
{
	return a.getPriority() > b.getPriority();
}

void AStar::Update(const vector<vector<bool>>& tileMap)
{
	AStar::tileMap = tileMap;

	if (!row && !col)
	{
		row = tileMap[0].size();
		col = tileMap.size();

		for (int i = 0; i < col; ++i)
		{
			openMap.push_back(vector<bool>());

			for (int j = 0; j < row; ++j)
				openMap[i].push_back(0);
		}
		for (int i = 0; i < col; ++i)
		{
			closeMap.push_back(vector<bool>());

			for (int j = 0; j < row; ++j)
				closeMap[i].push_back(0);
		}
		for (int i = 0; i < col; ++i)
		{
			dirMap.push_back(vector<int>());

			for (int j = 0; j < row; ++j)
				dirMap[i].push_back(0);
		}
	}
}

Path AStar::GetPath(const Vector2 & s, const Vector2 & g)
{
	static priority_queue<ASnode> pq[2]; // list of open (not-yet-tried) nodes
	static int pqi; // pq index
	static ASnode* n0;
	static ASnode* m0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	// reset the node maps
	for (y = 0; y < row; y++)
	{
		for (x = 0; x < col; x++)
		{
			closeMap[x][y] = 0;
			openMap[x][y] = 0;
		}
	}

	// create the start node and push into list of open nodes
	n0 = new ASnode(s.x, s.y, 0, 0);
	n0->updatePriority(g.x, g.y);
	pq[pqi].push(*n0);

	x = n0->getxPos(); y = n0->getyPos();
	openMap[x][y] = n0->getPriority(); // mark it on the open nodes map

											  // A* search
	while (!pq[pqi].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodes
		n0 = new ASnode(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // remove the node from the open list
		openMap[x][y] = 0;
		// mark it on the closed nodes map
		closeMap[x][y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == g.x && y == g.y)
		{
			// generate the path from finish to start
			// by following the directions
			Path path;

			while (!(x == s.x && y == s.y))
			{
				path.AddToPath(Vector2(x, y));

				j = dirMap[x][y];
				x += dx[j];
				y += dy[j];
			}

			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();

			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>col - 1 || ydy<0 || ydy>row - 1 || tileMap[xdx][ydy] == 1
				|| closeMap[xdx][ydy] == 1))
			{
				// generate a child node
				m0 = new ASnode(xdx, ydy, n0->getLevel(), n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(g.x, g.y);

				// if it is not in the open list then add into that
				if (openMap[xdx][ydy] == 0)
				{
					openMap[xdx][ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					// mark its parent node direction
					dirMap[xdx][ydy] = (i + dir / 2) % dir;
				}
				else if (openMap[xdx][ydy]>m0->getPriority())
				{
					// update the priority info
					openMap[xdx][ydy] = m0->getPriority();
					// update the parent direction info
					dirMap[xdx][ydy] = (i + dir / 2) % dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node

								   // empty the larger size pq to the smaller one
					if (pq[pqi].size()>pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better node instead
				}
				else delete m0; // garbage collection
			}
		}
		delete n0; // garbage collection
	}

	return Path(); // no route found
}
