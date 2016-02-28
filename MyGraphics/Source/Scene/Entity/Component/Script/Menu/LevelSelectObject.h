#pragma once

struct Vector2;
class Entity;

class LevelSelectObject
{
public:
	LevelSelectObject();
	~LevelSelectObject();
	
	Entity* AddLevel(const char* name, const char* level, const Vector2& position, Entity* owner);
	void PlayLevel(const char* level);
};