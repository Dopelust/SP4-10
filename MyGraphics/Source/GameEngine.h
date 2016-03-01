#pragma once

#include <vector>
using namespace std;

#define Engine GameEngine::Instance()

class GameState;
class GameEngine
{
public:
	static const int transitionRate = 16;

	float GetTransition();

	void ChangeState(GameState* state);

	void PushState(GameState* state);
	bool PopState();

	void Update(float dt);
	void Render();

	static GameEngine& Instance();

	void Terminate();
	bool IsActive();
private:
	GameEngine();
	~GameEngine();

	void ChangeState();

	vector<GameState*> states;
	GameState* queue;
	bool advance;

	float fps, elapsedTime, nextUpdate, transition;
	bool active, shouldTerminate;
};
