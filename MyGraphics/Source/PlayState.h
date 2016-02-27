#include "GameState.h"

class Sound;
class Button;
class Entity;
class TowerManager;

class PlayState : public GameState
{
public:
	void Init();
	void Exit();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

	static PlayState& Instance();

	Sound* bgm;
	Button* menu;
	TowerManager* tower;

private:
	PlayState();
	~PlayState();
};
