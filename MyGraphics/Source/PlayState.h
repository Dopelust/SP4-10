#include "GameState.h"

class Button;
class Entity;
class PlayState : public GameState
{
public:
	void Init();
	void Exit();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

	void HandleEvents();

	static PlayState& Instance();

	Button* menu;

private:
	PlayState();
	~PlayState();
};
