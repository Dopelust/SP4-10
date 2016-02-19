#include "TowerDatabase.h"
#include <iostream>
#include <fstream>
#include <istream>

map<string, map<string, TowerData>> TowerDatabase::towerData;

TowerDatabase::TowerDatabase()
{
	towerData.clear();
}

TowerDatabase::~TowerDatabase()
{
}

using namespace std;

#include "Utility.h"

bool TowerDatabase::Init(const char * type)
{
	cout << "Initializing tower database" << endl;

	ifstream towerDataFile(ToString("Data//Prefab//Tower//", type, ".txt").c_str());

	string line;
	string invis;

	string name;
	string towerName;
	string buildCost;
	string range;
	string cooldown;
	string textureName;
	string projectileName;
	string description;

	if (towerDataFile.is_open())
	{
		while (!towerDataFile.eof())
		{
			getline(towerDataFile, line, ' ');

			if (!(line.size() > 2 && line[0] == line[1] == '/'))
			{
				getline(towerDataFile, name, '\n');

				for (int i = 0; i < 7; ++i)
				{
					getline(towerDataFile, line, ',');
					getline(towerDataFile, invis, '	');

					getline(towerDataFile, towerName, ',');
					getline(towerDataFile, invis, '	');

					getline(towerDataFile, buildCost, ',');
					getline(towerDataFile, invis, '	');

					getline(towerDataFile, range, ',');
					getline(towerDataFile, invis, '	');

					getline(towerDataFile, cooldown, ',');
					getline(towerDataFile, invis, '	');
					
					getline(towerDataFile, textureName, ',');
					getline(towerDataFile, invis, '	');

					getline(towerDataFile, projectileName, ',');
					getline(towerDataFile, invis, '	');

					getline(towerDataFile, description, '\n');

					TowerData tower;
					tower.Set(towerName, stoi(buildCost), stoi(range), stof(cooldown), textureName, projectileName, description);
					
					towerData[type][line]= tower;
				}
			}
		}

		towerDataFile.close();
	}
	
	return true;
}

map<string, TowerData>& TowerDatabase::GetData(const char* type)
{
	return towerData[type];
}
