#include "ASnode.h"

ASnode::ASnode(int xp, int yp, int d, int p)
{
	xPos = xp; yPos = yp; level = d; priority = p;
}

int ASnode::getxPos() const
{
	return xPos;
}

int ASnode::getyPos() const
{
	return yPos;
}

int ASnode::getLevel() const
{
	return level;
}

int ASnode::getPriority() const
{
	return priority;
}

void ASnode::updatePriority(int xDest, int yDest)
{
	priority = level + estimate(xDest, yDest) * 10; //A*
}

void ASnode::nextLevel(int i)
{
//	level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
	level += 10;
}

#include "MyMath.h"

int ASnode::estimate(int xDest, int yDest)
{
	int xd = abs(xDest - xPos);
	int yd = abs(yDest - yPos);

	// Euclidian Distance
	return sqrt(xd*xd + yd*yd);

	// Manhattan distance
	//d=abs(xd)+abs(yd);

	// Chebyshev distance
	//d=max(abs(xd), abs(yd));
}
