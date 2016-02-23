#include "AStar.h"

#define MIN_COST (float) 1.0		// Minimum Permissible Cost	For Heuristics	
#define ALPHA    (float) 0.5		// Scaling Factor For Heuristics

const struct { int x, y; } succ[4] = { { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 } };

int AStar::GetPathLength()
{
	Node* temp;
	temp = current;

	int pathLength = 0;

	while (true)
	{
		if (temp != NULL)
		{
			++pathLength;
			temp = temp->child;
		}
		else
		{
			break;
		}
	}

	return pathLength;
}

void AStar::Update(vector<vector<bool>>& tileMap)
{
	this->tileMap = tileMap;

	if (NumRow && NumCol)
	{
		ResetNodeMap();
	}
	else
	{
		NumRow = tileMap[0].size();
		NumCol = tileMap.size();

		for (int i = 0; i < NumCol; ++i)
		{
			nodeMap.push_back(vector<Node>());

			for (int j = 0; j < NumRow; ++j)
			{
				nodeMap[i].push_back(Node(i, j));
			}
		}
	}
}

AStar::AStar() : goal(NULL), NumRow(0), NumCol(0)
{
}

AStar::~AStar()
{

}

AStar::AStar(const vector<vector<bool>>& tileMap) : goal(NULL), NumRow(0), NumCol(0)
{
	this->tileMap = tileMap;

	NumRow = tileMap[0].size();
	NumCol = tileMap.size();

	for (int i = 0; i < NumCol; ++i)
	{
		nodeMap.push_back(vector<Node>());

		for (int j = 0; j < NumRow; ++j)
		{
			nodeMap[i].push_back(Node(i, j));
		}
	}
}

// Get Best ( Minimum f ) Node From Open List
Node* AStar::GetBest()
{
	Node* best = NULL;

	for (int i = 0; i < NumCol; ++i)
		for (int j = 0; j < NumRow; ++j)
		{
			Node* node = GetNode(i, j);

			if (node->type == Node::NODE_OPEN)
			{
				if (best && node->f < best->f)
				{
					best = node;
				}
				else
				{
					best = node;
				}
			}

		}

	return best;
}

Node* AStar::GetNode(int x, int y)
{
	return &nodeMap[x][y];
}

// Get Neighborhood Nodes ( By Index ) Of Current Node
Node* AStar::GetSuccessor(Node *current, int i)
{
	Node *n = NULL;										// Null Initialisation
	int x = current->x + succ[i].x;						// Get x,y Position By Index
	int y = current->y + succ[i].y;

	if (y >= 0 && y < NumRow && x >= 0 && x < NumCol && tileMap[x][y] == false)		// If Grid Element Contains Empty Space
	{
		n = GetNode(x, y);									// Create A Node Object
	}
	
	return n;											// Return Successor Node
}

// Calculate Start To Current Node 'n' Cost
// Formula Below Reflects Scalability According To Cost Behavior
// ALPHA = Scaling Factor 
float AStar::Compute_g(Node* n)
{
	float dx = abs(start->x - n->x);
	float dy = abs(start->y - n->y);

	return 1 * (dx + dy);
}

// Calculate Cost From Start 'n' to Goal Node Using 'Manhattan' Distance Formula
float AStar::Compute_h(Node* n)
{
	float dx = abs(n->x - goal->x);
	float dy = abs(n->y - goal->y);

	return  1 * (dx + dy);
}

float AStar::Compute_g(const Vector2& n, const Vector2& start)
{
	float dx = abs(start.x - n.x);
	float dy = abs(start.y - n.y);

	return 1 * (dx + dy);
}

// Calculate Cost From Start 'n' to Goal Node Using 'Manhattan' Distance Formula
float AStar::Compute_h(const Vector2& n, const Vector2& goal)
{
	float dx = abs(n.x - goal.x);
	float dy = abs(n.y - goal.y);

	return  1 * (dx + dy);
}


// Check Whether Node 'n' Is In List
bool AStar::InOpen(Node *n)
{
	return n->type == Node::NODE_OPEN;
}

bool AStar::InClose(Node *n)
{
	return n->type == Node::NODE_CLOSE;
}

// Get From Open List Item As Specified In 'succ' Successor
Node* AStar::getFromOpenList(Node* succ)
{
	return GetNode(succ->x, succ->y);
}
// Get From Close List Item As Sspecified In 'succ' Successor
Node* AStar::getFromCloseList(Node* succ)
{
	return GetNode(succ->x, succ->y);
}

#include "../../GridInfo.h"

void AStar::ResetNodeMap()
{
	for (auto& list : nodeMap)
	{
		for (auto& node : list)
			node.Reset();
	}
}

// Search For Best Path ( Minimum Cost )
bool AStar::GetPath(Vector2 s, Vector2 g)
{
	ResetNodeMap();
	open = close = 0;

	current = NULL;

	start = GetNode(s.x, s.y);
	goal = GetNode(g.x, g.y);

	start->h = Compute_h(start);
	start->f = start->g + start->h;

	Node * temp = NULL;

	AddOpenList(start);									// Add Start Node To Open List
	while (open)					// Checking If Open List Is Empty
	{
		Node *n = GetBest();							// Get Best Node With Minimum 'f' Value
		
		if ((n->x == goal->x) && (n->y == goal->y))			// If Current Node 'n' Matches Goal Node in x,y Values
		{
			goal = current = n;
			
			while (n->parent != NULL)
			{
				n->parent->child = n;

				n = n->parent;
				current = n;
			}

			return true;
		}
		else											// Goal Not Reached Yet 
		{
			RemoveOpenList(n);							// Remove Node From Open List Since It Has Been Examined
			AddCloseList(n);							// Add To Examined (Close) List

			// Define Temporary Node
			for (int i = 0; i < 4; i++) 
			{			
				Node* successor = GetSuccessor(n, i);			// Get Successor Node By Index

				if (successor)						// If A Valid Space For A Successor Node
				{
					successor->g = Compute_g(successor);		// Calculate 'g' Cost Value
					successor->h = Compute_h(successor);		// Calculate 'h' Cost Value
					successor->f = successor->g + successor->h;   // Calculate 'f' Cost Value
				
					if (InOpen(successor))						// If Proposed Succesor Exists In Open List..
					{
						temp = getFromOpenList(successor);				// Get The Node Concerned
						if (temp->f > successor->f)						// Check If Successor's 'f' Value Is Lower
						{
							RemoveOpenList(temp);						// If lower, Remove Existing Node From Open List
							AddOpenList(successor);						// Add Successor To Open List Instead
						}
					}
					else if (InClose(successor))						// If Proposed Succesor Exists In Close List..
					{
						temp = getFromCloseList(successor);				// Get The Node Concerned
						if (temp->f > successor->f)						// Check If Successor's 'f' Value Is Lower
						{
							RemoveCloseList(temp);						// Remove From Close List
							AddCloseList(successor);					// Add Successor To Close List
						}
					}
					else												// if Not In Either Open Or Close List ie : New ...
					{
						AddOpenList(successor);						// Add Successor To Open List
						successor->parent = n;						// Link Back To Parent/Current Node
					}
				}
			}
		}
	}

	return false;

}

// Add To Open List, Show Its Content
void AStar::AddOpenList(Node *n)
{
	++open;
	n->type = Node::NODE_OPEN;
}
// Add To Close List, Show Its Content
void AStar::AddCloseList(Node *n)
{
	++close;
	n->type = Node::NODE_CLOSE;
}

// Remove Node From Open List After It Is Examined For Minimum 'f' Value
void AStar::RemoveOpenList(Node *n)
{
	--open;
	n->type = Node::NODE_UNDEFINED;
}

// Remove Node From Close List After It Is Examined For Minimum 'f' Value
void AStar::RemoveCloseList(Node *n)
{
	--close;
	n->type = Node::NODE_UNDEFINED;
}

Node::Node(int x, int y) :parent(NULL), child(NULL), f(0.0), g(0.0), h(0.0), x(x), y(y), type(NODE_UNDEFINED)
{
}

void Node::Reset()
{
	parent = child = NULL;
	f = g = h = 0;
	type = NODE_UNDEFINED;
}