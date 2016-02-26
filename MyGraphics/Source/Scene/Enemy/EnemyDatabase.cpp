#include "EnemyDatabase.h"
#include <iostream>
#include <fstream>
#include <istream>

vector<EnemyData> EnemyDatabase::enemyData;

EnemyDatabase::EnemyDatabase()
{
	enemyData.clear();
}

EnemyDatabase::~EnemyDatabase()
{
}

using namespace std;

#include "FileSystem.h"
#include "Utility.h"

bool EnemyDatabase::Init(const char * fileData)
{
	cout << "Initializing projectile database" << endl;

	vector<string>& lines = FileSystem::Instance()->GetLines(ToString("Data//Prefab//Enemy//", fileData, ".txt"));

	if (lines.empty())
		return false;

	for (auto& line : lines)
	{
		if (line.size() > 2 && line[0] == '/' && line[1] == '/')
			continue;

		RemoveChar(line, '	'); //Remove whitespaces
		vector<string>& data = DivideLine(line, ','); //Divide lines by comma
	
		EnemyData enemy;
		if (stoi(data[4]) == 0)
		{
			enemy.Set(data[0], stoi(data[1]), stof(data[2]), stoi(data[3]), false, stoi(data[5]));
		}
		else
		{
			enemy.Set(data[0], stoi(data[1]), stof(data[2]), stoi(data[3]), false, stoi(data[5]));
		}

		enemyData.push_back(enemy);
	}

	return true;
}

EnemyData& EnemyDatabase::GetData(int tier)
{
	return enemyData[tier];
}
