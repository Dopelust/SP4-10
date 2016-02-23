#pragma once

#include "Vector2.h"

#include <vector>
using namespace::std;

class Grid;

class Node
{
public:
	Node(int x, int y);

	Node *parent, *child;	// Link To Previous Node On Best Path
	int x, y;		// x,y Position Of Grid
	float f, g, h;	// Cost Elements : g = Cost From Start To Current Node
					//                 h = Cost From Current To Goal Node
					//				   f = Cost From Start To Goal (g+h) Node

	void Reset();

	enum NodeType
	{
		NODE_UNDEFINED,
		NODE_OPEN,
		NODE_CLOSE,
	};

	NodeType type;
};

class AStar
{
public:
	//Grid* grid;
	vector<vector<bool>> tileMap;
	vector<vector<Node>> nodeMap;

	void ResetNodeMap();
	Node* GetNode(int x, int y);

	int NumRow;
	int NumCol;

	Node* start, *current, *goal;

	int GetPathLength();
	void Update(vector<vector<bool>>& tileMap);

	int open;
	int close;

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
	float Compute_g(const Vector2& n, const Vector2& start);				// Calculate 'g' Cost
	float Compute_h(const Vector2& n, const Vector2& goal);				// Calculate 'h' Cost

	bool InOpen(Node *n); // Check If Node 'n' Is In List
	bool InClose(Node *n); // Check If Node 'n' Is In List

	bool GetPath(Vector2 s, Vector2 g);							// Search For Best Path

	Node* AStar::getFromOpenList(Node* succ); // Get From List Item Same As 'succ' Successor
	Node* AStar::getFromCloseList(Node* succ);
};
