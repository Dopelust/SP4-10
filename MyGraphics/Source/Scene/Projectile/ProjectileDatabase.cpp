#include "ProjectileDatabase.h"
#include <iostream>
#include <fstream>
#include <istream>

map<string, ProjectileData> ProjectileDatabase::projectileData;

ProjectileDatabase::ProjectileDatabase()
{
	projectileData.clear();
}

ProjectileDatabase::~ProjectileDatabase()
{
}

using namespace std;

bool ProjectileDatabase::Init(const char * fileData)
{
	cout << "Initializing Projectile database" << endl;

	ifstream ProjectileDataFile(fileData);

	string line;
	string invis;

	string name;
	string projectileName;
	string speed;
	string range;
	string pierce;
	string effect;

	if (ProjectileDataFile.is_open())
	{
		while (!ProjectileDataFile.eof())
		{
			getline(ProjectileDataFile, line, ' ');

			if (!(line.size() > 2 && line[0] == line[1] == '/'))
			{
				getline(ProjectileDataFile, name, '\n');

				getline(ProjectileDataFile, projectileName, ',');
				getline(ProjectileDataFile, invis, ' ');

				getline(ProjectileDataFile, speed, ',');
				getline(ProjectileDataFile, invis, ' ');

				getline(ProjectileDataFile, range, ',');
				getline(ProjectileDataFile, invis, ' ');

				getline(ProjectileDataFile, pierce, ',');
				getline(ProjectileDataFile, invis, ' ');

				getline(ProjectileDataFile, effect, '\n');
				
				ProjectileData::ProjectileEffect eff = ProjectileData::NONE;

				if (effect == "NORMAL")
					eff = ProjectileData::NORMAL;
				else if (effect == "SLOW")
					eff = ProjectileData::SLOW;
				else if (effect == "STUN")
					eff = ProjectileData::STUN;
				
				ProjectileData proj;
				proj.Set(projectileName, stof(speed), stof(range), stoi(pierce), eff);

				projectileData[name] = proj;
			}
		}
		ProjectileDataFile.close();
	}
	
	return true;
}

ProjectileData& ProjectileDatabase::GetData(string type)
{
	return projectileData[type];
}
