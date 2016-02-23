#ifndef STAGE_DATABASE_H
#define STAGE_DATABASE_H

#include "StageData.h"

#include <map>
#include <vector>
#include <string>

using std::map;
using std::vector;
using std::string;

class StageDatabase
{
public:
	static bool Init(const char * fileData);
	static StageData& GetData(string stageName);

private:
	StageDatabase();
	~StageDatabase();

	static map<string, StageData> stageData;
};

#endif