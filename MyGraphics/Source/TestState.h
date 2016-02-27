#include "GameState.h"

class InputField;
class Button;
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

	Button* menu;
	Button* load;
	Button* save;

	InputField* input;

private:
	TestState();
	~TestState();
};
