#include "GameState.h"

#include <string>
using namespace::std;

class Sound;
class Button;
class Entity;
class TowerManager;
class StageManager;

class PlayState : public GameState
{
public:
	void Init();
	void Exit();

	string level;

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

	static PlayState& Instance();

	Sound* bgm;
	Button* menu;

	StageManager* stage;
	TowerManager* tower;

private:
	PlayState();
	~PlayState();
};
