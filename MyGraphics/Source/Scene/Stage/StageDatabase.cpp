#include "StageDatabase.h"
#include <iostream>
#include <fstream>
#include <istream>

map<string, StageData> StageDatabase::stageData;

StageDatabase::StageDatabase()
{
	stageData.clear();
}

StageDatabase::~StageDatabase()
{
}

using namespace std;

#include "FileSystem.h"
#include "Utility.h"

bool StageDatabase::Init(const char * fileData)
{
	cout << "Initializing projectile database" << endl;

	vector<string>& lines = File.GetLines(ToString("Data//Levels//", fileData, ".txt"));

	if (lines.empty())
		return false;

	StageData stage;
	WaveData wave;

	for (auto& line : lines)
	{
		if (line.size() > 2 && line[0] == '/' && line[1] == '/')
		{
			continue;
		}
		else if (line.empty())
		{
			stage.AddWave(wave);
			wave.Reset();
			continue;
		}
		
		RemoveChar(line, '	'); //Remove whitespaces
		vector<string>& data = DivideLine(line, ','); //Divide lines by comma

		if (data[0] == "Wave")
		{
			stage.startHealth = stoi(data[1]);
			stage.startGold = stoi(data[2]);
			continue;
		}

		if (stoi(data[3]) == 0)
		{
			wave.Add(stoi(data[0]), stof(data[1]), stoi(data[2]), false);
		}
		else
		{
			wave.Add(stoi(data[0]), stof(data[1]), stoi(data[2]), true);
		}
	}

	stageData[fileData] = stage;

	return true;
}

StageData& StageDatabase::GetData(string stageName)
{
	return stageData[stageName];
}
