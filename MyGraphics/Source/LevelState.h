#include "GameState.h"

class Entity;
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

private:
	MenuState();
	~MenuState();
};
