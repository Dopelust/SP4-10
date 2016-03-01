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
	static void Exit();

	static vector<TowerData>& GetData(const char* type);
	static int GetMaxUpgrade(const char* type);
	static int GetSellPrice(const char* type, int upgrade);
private:
	static map<string, vector<TowerData>> towerData;

	TowerDatabase();
	~TowerDatabase();
};

#endif