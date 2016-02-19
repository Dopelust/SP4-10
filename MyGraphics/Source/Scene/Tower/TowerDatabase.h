#ifndef TOWER_DATABASE_H
#define TOWER_DATABASE_H

#include "TowerData.h"

#include <vector>
using std::vector;

class TowerDatabase
{
public:
	// Parse data file and store
	static bool Init(const char * type);
	static map<string, TowerData>& GetData(const char* type);

private:
	static map<string, map<string, TowerData>> towerData;

	TowerDatabase();
	~TowerDatabase();
};

#endif