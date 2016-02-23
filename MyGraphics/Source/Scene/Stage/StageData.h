#ifndef STAGE_DATA_H
#define STAGE_DATA_H

#include <iostream>
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

	inline void Add(int tier, float delay, int count)
	{
		this->tier.push_back(tier);
		this->delay.push_back(delay);
		this->count.push_back(count);
	}

	inline void Print()
	{
		std::cout << "Tier, Delay, Count" << std::endl;
		for (int i = 0; i < tier.size(); ++i)
		{
			std::cout << tier[i] + ", ";
			std::cout << delay[i];
			std::cout << ", " + count[i] << std::endl;
		}
	}

	inline void Reset()
	{
		tier.clear();
		delay.clear();
		count.clear();
	}

	vector<int> tier;
	vector<float> delay;
	vector<int> count;
};

class StageData
{
public:
	StageData()
	{

	}

	~StageData()
	{

	}

	inline void AddWave(WaveData waveData)
	{
		stageData.push_back(waveData);
	}

	vector<WaveData> stageData;
};

#endif