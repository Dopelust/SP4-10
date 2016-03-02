#pragma once

#include "../../Component.h"
#include "LevelSelectObject.h"

#include <map>
using namespace::std;

class CSVRenderer;
class InputField;
class Button;

class LevelScript : public Component, public LevelSelectObject
{
public:
	LevelScript();
	~LevelScript();

	void Init(Entity* ent);
	void Update(double dt);	
	void AddLevel(const char* name, const char* level, const Vector2& position, Entity* owner);

private:
	CSVRenderer* csv;
	InputField* input;
	Button* play;
	Button* editor;
};