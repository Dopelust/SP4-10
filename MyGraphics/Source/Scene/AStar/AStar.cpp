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
	NumRow = tileMap[0].size();
	NumCol = tileMap.size();
}

Node* AStar::GetStartNode()
{
	return current;
}

AStar::AStar() : goal(NULL)
{
}

AStar::~AStar()
{

}

AStar::AStar(const vector<vector<bool>>& tileMap) : goal(NULL)
{
	this->tileMap = tileMap;

	NumRow = tileMap[0].size();
	NumCol = tileMap.size();
}

void AStar::Traverse()
{
	if (current->child)
		current = current->child;
}

// Get Best ( Minimum f ) Node From Open List
Node* AStar::GetBest()
{
	int best = 0;										// Initialise Best (Minimum f) Index=0 For Start Of Comparison
	for (int i = 1; i < (int)openList.size(); i++) {
		if (openList[i]->f < openList[best]->f) {		// Comparing ..
			best = i;									// Get Index With Lower 'f' Value
		}
	}

	return openList[best];								// return the best node
}

// Get Neighborhood Nodes ( By Index ) Of Current Node
Node* AStar::GetSuccessor(Node *current, int i)
{
	Node *n = NULL;										// Null Initialisation
	int x = current->x + succ[i].x;						// Get x,y Position By Index
	int y = current->y + succ[i].y;

	if (y >= 0 && y < NumRow && x >= 0 && x < NumCol &&
		tileMap[x][y] == false)		// If Grid Element Contains Empty Space
	{
		n = new Node;									// Create A Node Object
		n->x = x;										// Initialise To x-y Value Of Successor
		n->y = y;
	}
	
	return n;											// Return Successor Node
}

// Calculate Start To Current Node 'n' Cost
// Formula Below Reflects Scalability According To Cost Behavior
// ALPHA = Scaling Factor 
float AStar::Compute_g(Node* n) {
	float tempG;
	if (n->parent != NULL) tempG = n->parent->g;
	else tempG = n->g;
	return (float)(1.0 + ALPHA * (tempG - 1.0));
}

// Calculate Cost From Start 'n' to Goal Node Using 'Manhattan' Distance Formula
float AStar::Compute_h(Node* n)
{
	return  (float)(MIN_COST*(abs((float)n->x - (float)goal->x) + abs((float)n->y - (float)goal->y)));
}

// Check Whether Node 'n' Is In List
bool AStar::InList(vector <Node*> list, Node *n)
{
	for (int i = 0; i<(int)list.size(); i++)
	{
		if ((list[i]->x == n->x) && (list[i]->y == n->y))
		{
			return  true;			// If Found In List
		}
	}
	return false;					// If Not In List
}

// Get From Open List Item As Specified In 'succ' Successor
Node* AStar::getFromOpenList(Node* succ)
{
	Node *n;
	for (int i = 0; i<(int)openList.size(); i++)	// Loop Through List		
	{
		if ((openList[i]->x == succ->x) && (openList[i]->y == succ->y))	// Have A Match ...
		{
			n = openList[i];													// Pick The Node
			break;
		}
	}
	return n;
}
// Get From Close List Item As Sspecified In 'succ' Successor
Node* AStar::getFromCloseList(Node* succ)
{
	Node *n;
	for (int i = 0; i<(int)closeList.size(); i++)  // Loop Through List
	{
		if ((closeList[i]->x == succ->x) && (closeList[i]->y == succ->y)) // Have A Match ...
		{
			n = closeList[i];											   // Pick The Node
			break;
		}
	}
	return n;
}
#include <string>
using namespace std;
void AStar::ShowPath(Node *walker)
{
	vector<int> xpos;
	vector<int> ypos;
	cout << "\nBEST PATH SOLUTION";

	vector<vector<string>> print;
	for (int i = 0; i < NumRow; ++i)
	{
		print.push_back(vector<string>());

		for (int j = 0; j < NumCol; ++j)
		{
			print[i].push_back(" ");
		}
	}

	// Get Node On Best Path Linked To Goal 
	while (walker != NULL)		// If Start Point IS Not NULL
	{
		print[walker->y][walker->x] = '*';	// Grid Map Node Is Marked As Best Path Node


		xpos.push_back(walker->x);
		ypos.push_back(walker->y);

		walker = walker->parent;		// Go To Next Link To The Path

	}

	cout << "\n";
	for (int y = 0; y< print.size(); y++)			// Loop Through 2D Array To Show Map & Path
	{
		for (int x = 0; x< print[y].size(); x++)
		{
			cout << print[y][x];
		}
		cout << "\n";
	}
	cout << "\n";

	for (int i = 0; i < xpos.size(); ++i)
	{
		cout << "x: " << xpos[i] << " y: " << ypos[i] << endl;
	}
}

#include "../../GridInfo.h"

bool AStar::GetPathBeside(Vector2 s, Vector2 g)
{
	Vector2 goal[4];
/*
	goal[0].Set(g.x, g.y + grid->GetTileHeight());
	goal[1].Set(g.x, g.y - grid->GetTileHeight());
	goal[2].Set(g.x + grid->GetTileWidth(), g.y);
	goal[3].Set(g.x - grid->GetTileWidth(), g.y);*/

	float nearest = 9999 * 9999;
	int index = 0;

	for (int i = 0; i < 4; ++i)
	{
		if (goal[i].DistSquared(s) < nearest)
		{
			nearest = goal[i].DistSquared(s);
			index = i;
		}
	}

	return GetPath(s, goal[index]);
}

// Search For Best Path ( Minimum Cost )
bool AStar::GetPath(Vector2 s, Vector2 g)
{
	while (goal != NULL)		// If Start Point IS Not NULL
	{
		Node* temp = goal;
		goal = goal->parent;
		delete temp;
	}
	openList.clear();
	closeList.clear();
	current = NULL;

	Node* start = new Node;									// Create Node Objects & Allocate Memory
	goal = new Node;
	start->x = s.x; start->y = s.y;
	goal->x = g.x; goal->y = g.y;		// Set Start and Goal x-y Values

	start->h = Compute_h(start);
	start->f = start->g + start->h;

	Node * temp = NULL;

	AddOpenList(start);									// Add Start Node To Open List
	while ((int)openList.size() != 0)					// Checking If Open List Is Empty
	{
		Node *n = GetBest();							// Get Best Node With Minimum 'f' Value
		//cout << "Getting best node (minimum f) ... ";
		//printInfo(n->x, n->y, n->f, n->g, n->h);						// List The Node Info
		//cout << "Matching  (" << n->x << "," << n->y << ") with  goal ";
		//cout << "(" << goal->x << "," << goal->y << ")" << endl;
		//cin.get();									// UNCOMMENT TO SEE INTERMEDIATE RESULTS		
		if ((n->x == goal->x) && (n->y == goal->y))			// If Current Node 'n' Matches Goal Node in x,y Values
		{
			delete goal;
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
			Node *successor;							// Define Successor Node
			// Define Temporary Node
			for (int i = 0; i < 4; i++) {				// Loop Through 4 Neighborhood Nodes By Their Index
				successor = GetSuccessor(n, i);			// Get Successor Node By Index
				if (successor != NULL)						// If A Valid Space For A Successor Node
				{
					successor->parent = n;						// Link Back To Parent/Current Node
					successor->g = Compute_g(successor);		// Calculate 'g' Cost Value
					successor->h = Compute_h(successor);		// Calculate 'h' Cost Value
					successor->f = successor->g + successor->h;   // Calculate 'f' Cost Value
					//cout << "Getting successor ....";
					//printInfo(successor->x, successor->y, successor->f, successor->g, successor->h);	// List Successor x,y,f Values
					if (InList(openList, successor))						// If Proposed Succesor Exists In Open List..
					{
						temp = getFromOpenList(successor);				// Get The Node Concerned
						if (temp->f > successor->f)						// Check If Successor's 'f' Value Is Lower
						{
							RemoveOpenList(temp);						// If lower, Remove Existing Node From Open List
							AddOpenList(successor);						// Add Successor To Open List Instead
						}
					}
					else
					if (InList(closeList, successor))						// If Proposed Succesor Exists In Close List..
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
					}
				}
			}
		}
	}
	cout << "A path finder could not find a path" << endl;

	return false;					// Return False(Not Found)

}

// Add To Open List, Show Its Content
void AStar::AddOpenList(Node *n)
{
	openList.push_back(n);
}
// Add To Close List, Show Its Content
void AStar::AddCloseList(Node *n)
{
	closeList.push_back(n);
}

// Remove Node From Open List After It Is Examined For Minimum 'f' Value
void AStar::RemoveOpenList(Node *n)
{
	for (int i = 0; i<(int)openList.size(); i++)	// Go Through Open List Items
	{
		if ((openList[i]->x == n->x) && (openList[i]->y == n->y)) // If Found The Item 
		{							// List Node(To Erase) x,y,f Values
			openList.erase(openList.begin() + i, openList.begin() + i + 1);	// Erase Item From List	
			break;
		}
	}
}

// Remove Node From Close List After It Is Examined For Minimum 'f' Value
void AStar::RemoveCloseList(Node *n)
{
	for (int i = 0; i<(int)closeList.size(); i++)	// Go Through Close List Items
	{
		if ((closeList[i]->x == n->x) && (closeList[i]->y == n->y)) // If Found The Item 
		{							// List Node(To Erase) x,y,f Values
			closeList.erase(closeList.begin() + i, closeList.begin() + i + 1);	// Erase Item From List	
			break;
		}
	}
}

Node::Node() :parent(NULL), child(NULL), f(0.0), g(0.0), h(0.0)
{
}
