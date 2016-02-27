#include "GameState.h"

class MenuHandler;
class MenuState : public GameState
{
public:
	void Init();
	void Exit();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();
	
	static MenuState& Instance();

private:
	MenuState();
	~MenuState();

	MenuHandler* menu;
};
