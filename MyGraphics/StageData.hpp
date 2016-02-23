#ifndef STAGE_DATA_H
#define STAGE_DATA_H

#include <map>
#include <vector>

using namespace std;

struct WaveData
{
	WaveData() :
	tier(0),
	delay(0),
	count(0)
	{

	}

	~WaveData()
	{

	}

	inline void Set(int tier, float delay, int count)
	{
		this->tier = tier;
		this->delay = delay;
		this->count = count;
	}

	int tier;
	float delay;
	int count;
};

class StageData
{
	StageData()
	{

	}

	~StageData()
	{

	}

	inline void SetWave(string waveNo, int tier, float delay, int count)
	{
		WaveData data;
		data.Set(tier, delay, count);
		stageData[waveNo].push_back(data);
	}

	map<string, vector<WaveData>> stageData;
};

#endif