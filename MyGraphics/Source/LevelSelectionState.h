#include "GameState.h"

class Button;
class LevelSelectionState : public GameState
{
public:
	void Init();
	void Exit();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

	void HandleEvents();

	static LevelSelectionState& Instance();

	Button* level1,*level2,*level3,*level4;
	Button* custom;
	Button* Return;

private:
	LevelSelectionState();
	~LevelSelectionState();
};
