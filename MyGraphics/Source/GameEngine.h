#pragma once

#include <vector>
using namespace std;

#define Engine GameEngine::Instance()

class GameState;
class GameEngine
{
public:
	void ChangeState(GameState* state);

	void PushState(GameState* state);
	bool PopState();

	void Update(float dt);
	void Render();
	void HandleEvents();

	static GameEngine& Instance();

	void Terminate();
	bool IsActive();
private:
	GameEngine();
	~GameEngine();

	vector<GameState*> states;

	float fps, elapsedTime, nextUpdate;
	bool active;
};
