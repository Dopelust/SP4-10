#pragma once

#define Time TimeSystem::Instance()

class Application;

class TimeSystem
{
public:
	static TimeSystem& Instance();

	float GetDeltaTime();
	float GetUnscaledTime();

	void SetTimeScale(float scale);

private:
	friend Application;

	TimeSystem();
	~TimeSystem();

	void SetDeltaTime(float dt);

	float dt;
	float dt_scaled;

	float scale;
};