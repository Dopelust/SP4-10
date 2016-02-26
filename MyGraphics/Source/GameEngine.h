#pragma once

#include <vector>
using namespace std;

#define Engine GameEngine::Instance()

class GameState;
class GameEngine
{
public:
	static const int transitionRate = 8;

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

	void ChangeState();

	vector<GameState*> states;
	GameState* queue;

	float fps, elapsedTime, nextUpdate, transition;
	bool active;
};
