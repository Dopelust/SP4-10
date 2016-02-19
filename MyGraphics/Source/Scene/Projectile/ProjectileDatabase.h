#ifndef PROJECTILE_DATABASE_H
#define PROJECTILE_DATABASE_H

#include "ProjectileData.h"

#include <map>
#include <string>

using std::map;
using std::string;

class ProjectileDatabase
{
public:
	static bool Init(const char * fileData);
	static ProjectileData& GetData(string type);

private:
	ProjectileDatabase();
	~ProjectileDatabase();

	static map<string, ProjectileData> projectileData;
};

#endif