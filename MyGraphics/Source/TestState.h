#include "GameState.h"

class InputField;
class Button;
class Entity;

class TestState : public GameState
{
public:
	void Init();
	void Exit();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

	static TestState& Instance();
	
	Entity* popup;

	Button* menu;
	Button* load;
	Button* save;
	Button* remove;
	
	InputField* input;

private:
	TestState();
	~TestState();
};
