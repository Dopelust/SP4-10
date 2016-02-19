#pragma once

#include "Vector2.h"

#include <vector>
using namespace::std;

class Grid;

class Node
{
public:
	Node();
	Node *parent, *child;	// Link To Previous Node On Best Path
	int x, y;		// x,y Position Of Grid
	float f, g, h;	// Cost Elements : g = Cost From Start To Current Node
					//                 h = Cost From Current To Goal Node
					//				   f = Cost From Start To Goal (g+h) Node
};

class AStar
{
public:
	//Grid* grid;
	vector<vector<bool>> tileMap;

	int NumRow;
	int NumCol;

	Node* current;

	Node* GetStartNode();
	int GetPathLength();
	void Update(vector<vector<bool>>& tileMap);

	void Traverse();

	Node* goal;

	vector <Node *> openList;				// Container For Open List ( nodes[list] To Examine When Searching)
	vector <Node *> closeList;				// Container For Close List (Nodes Already Examined)
	AStar();
	~AStar();
	AStar(const vector<vector<bool>>& tileMap);		// Constructor For Initialising Start And Goal x,y Nodes
	void AddOpenList(Node *n);				// Add Node To Open list
	void AddCloseList(Node *n);				// Add Node To Close List
	void RemoveOpenList(Node *n);			// Remove Node From Open List
	void RemoveCloseList(Node *n);			// Remove Node From Close List
	Node* GetBest();						// Get Best Node (Minimum f) In Open List
	Node* GetSuccessor(Node *current, int i);// Get Neighborhood Nodes( Empty Space) Of Current Node Given A Neighborhood Index 
	float Compute_g(Node* n);				// Calculate 'g' Cost
	float Compute_h(Node* n);				// Calculate 'h' Cost
	bool InList(vector <Node*> list, Node *n); // Check If Node 'n' Is In List

	bool GetPathBeside(Vector2 s, Vector2 g);
	bool GetPath(Vector2 s, Vector2 g);							// Search For Best Path
	void ShowPath(Node *walker);

	Node* AStar::getFromOpenList(Node* succ); // Get From List Item Same As 'succ' Successor
	Node* AStar::getFromCloseList(Node* succ);
};
