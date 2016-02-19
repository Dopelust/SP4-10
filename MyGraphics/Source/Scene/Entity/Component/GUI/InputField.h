#pragma once

#include "../Component.h"

#include <string>
using namespace::std;

class Transform;
class TextRenderer2D;
class Button;

class InputField : public Component
{
public:
	InputField();
	~InputField();

	void SetTicker(Entity* ticker);
	void SetLimit(int limit);
	void SetActivator(Button* activator);

	void Init(Entity* ent);
	void Update(double dt);

	void SetTextRenderer(TextRenderer2D* renderer);

	string GetOutput();
	void SetOutput(const char* output);

private:
	Entity* root, *ticker;
	Button* activator;

	TextRenderer2D* renderer;
	string output;

	int limit;
	float timer;
	bool focus;
};