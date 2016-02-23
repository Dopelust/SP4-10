#include "GameState.h"

class Button;
class MenuState : public GameState
{
public:
	void Init();
	void Exit();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

	void HandleEvents();

	static MenuState& Instance();

	Button* play;
	Button* editor;
	Button* option;
	Button* exit;

private:
	MenuState();
	~MenuState();
};
