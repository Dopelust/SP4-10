#include "TowerDatabase.h"
#include <iostream>
#include <fstream>
#include <istream>

map<string, vector<TowerData>> TowerDatabase::towerData;

TowerDatabase::TowerDatabase()
{
	towerData.clear();
}

TowerDatabase::~TowerDatabase()
{
}

using namespace std;

#include "FileSystem.h"
#include "Utility.h"

bool TowerDatabase::Init(const char * type)
{
	cout << "Initializing tower database" << endl;

	vector<string>& lines = FileSystem::Instance()->GetLines(ToString("Data//Prefab//Tower//", type, ".txt"));

	if (lines.empty())
		return false;

	for (auto& line : lines)
	{
		if (line.size() > 2 && line[0] == '/' && line[1] == '/')
			continue;

		RemoveChar(line, '	'); //Remove whitespaces
		vector<string>& data = DivideLine(line, ','); //Divide lines by comma

		TowerData tower;
		tower.Set(stof(data[0]), stof(data[1]), stof(data[2]), stoi(data[3]), stof(data[4]), stoi(data[5]), stof(data[6]), stoi(data[7]), data[8], data[9], data[10]);

		towerData[type].push_back(tower);
	}

	return true;
}

void TowerDatabase::Exit()
{
	return towerData.clear();
}

vector<TowerData>& TowerDatabase::GetData(const char* type)
{
	return towerData[type];
}

#include "MyMath.h"

int TowerDatabase::GetMaxUpgrade(const char * type)
{
	return Math::Min((int)GetData(type).size() - 1, 4);
}
