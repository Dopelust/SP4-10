#ifndef ENEMY_DATABASE_H
#define ENEMY_DATABASE_H

#include "EnemyData.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

class EnemyDatabase
{
public:
	static bool Init(const char * fileData);
	static EnemyData& GetData(int type);

private:
	EnemyDatabase();
	~EnemyDatabase();

	static vector<EnemyData> enemyData;
};

#endif