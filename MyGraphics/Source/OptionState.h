#include "GameState.h"
#include "SoundEngine.h"
class Button;
class Slider;
class OptionState : public GameState
{
public:
	void Init();
	void Exit();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

	void HandleEvents();

	static OptionState& Instance();

	bool bgm;
	bool sfx;

	Button* back;
	Slider* slider;
	ISound* datsound;

	float volume = 50.f;
private:
	OptionState();
	~OptionState();
};
