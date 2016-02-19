#pragma once

class Scene;
class GameState
{
public:
	GameState();
	virtual ~GameState();

	virtual void Init() = 0;
	virtual void Exit() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual void HandleEvents() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

protected:
	Scene* scene;
};
