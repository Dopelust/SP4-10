#include "Time.h"

TimeSystem::TimeSystem() : scale(1)
{
}

TimeSystem::~TimeSystem()
{
}

TimeSystem& TimeSystem::Instance()
{
	static TimeSystem time;
	return time;
}

float TimeSystem::GetDeltaTime()
{
	return dt_scaled;
}
float TimeSystem::GetUnscaledTime()
{
	return dt;
}

void TimeSystem::SetDeltaTime(float dt)
{
	this->dt = dt;
	this->dt_scaled = dt * scale;
}

void TimeSystem::SetTimeScale(float scale)
{
	this->scale = scale;
	this->dt_scaled = dt * scale;
}