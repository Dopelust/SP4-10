//#include "ProjectileDatabase.h"
//#include <iostream>
//#include <fstream>
//#include <istream>
//
//map<string, ProjectileData> ProjectileDatabase::projectileData;
//
//ProjectileDatabase::ProjectileDatabase()
//{
//	projectileData.clear();
//}
//
//ProjectileDatabase::~ProjectileDatabase()
//{
//}
//
//using namespace std;
//
//#include "FileSystem.h"
//#include "Utility.h"
//
//bool ProjectileDatabase::Init(const char * fileData)
//{
//	cout << "Initializing projectile database" << endl;
//
//	vector<string>& lines = FileSystem::Instance()->GetLines(ToString("Data//Prefab//Projectile//", fileData, ".txt"));
//
//	if (lines.empty())
//		return false;
//
//	for (auto& line : lines)
//	{
//		if (line.size() > 2 && line[0] == '/' && line[1] == '/')
//			continue;
//
//		RemoveChar(line, '	'); //Remove whitespaces
//		vector<string>& data = DivideLine(line, ','); //Divide lines by comma
//
//		ProjectileData::ProjectileEffect effect;
//		effect = ProjectileData::ProjectileEffect::NONE;
//
//		if (data[1] == "NORMAL")
//		{
//			effect = ProjectileData::ProjectileEffect::NORMAL;
//		}
//		else if (data[1] == "SLOW")
//		{
//			effect = ProjectileData::ProjectileEffect::SLOW;
//		}
//		else if (data[1] == "STUN")
//		{
//			effect = ProjectileData::ProjectileEffect::STUN;
//		}
//
//		ProjectileData projectile;
//		projectile.Init(data[0], effect);
//
//		projectileData[fileData] = projectile;
//	}
//
//	return true;
//}
//
//ProjectileData& ProjectileDatabase::GetData(string type)
//{
//	return projectileData[type];
//}
