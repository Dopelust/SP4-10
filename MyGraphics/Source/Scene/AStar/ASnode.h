#pragma once

class ASnode
{
	// current position
	int xPos;
	int yPos;
	// total distance already travelled to reach the node
	int level;
	// priority=level+remaining distance estimate
	int priority;  // smaller: higher priority

public:
	ASnode(int xp, int yp, int d, int p);

	int getxPos() const;
	int getyPos() const;
	int getLevel() const;
	int getPriority() const;

	void updatePriority(int xDest, int yDest);

	// give better priority to going strait instead of diagonally
	void nextLevel(int i); // i: direction

	// Estimation function for the remaining distance to the goal.
	int estimate(int xDest, int yDest);
};