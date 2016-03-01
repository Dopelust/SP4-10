#include "../../../../Scene.h"
#include "../../../Entity.h"
#include "../../../EntityFactory.h"
#include "../../Transform.h"

#include "Vector2.h"

#include "MenuHandler.h"
#include "StateObject.h"

#include "MenuScript.h"
#include "OptionScript.h"
#include "LevelHandler.h"
#include "AchievementScript.h"

#include "../../../../../SoundEngine.h"

MenuHandler::MenuHandler()
{
}

MenuHandler::~MenuHandler()
{
}

void MenuHandler::Init(Entity * ent)
{
	AddState(ent->AddChild("Menu")->AddComponent<MenuScript>());
	Push(GetState<MenuScript>());

	AddState(ent->AddChild("Options")->AddComponent<OptionScript>());

	AddState(ent->AddChild("Achievements")->AddComponent<AchievementScript>());

	AddState(ent->AddChild("Level Selection")->AddComponent<LevelHandler>());

	bgm = Audio.Play2D("Night Changes", 1);
}

void MenuHandler::Update(double dt)
{
	StateHandler::Update(dt);

	if (bgm->isFinished())
		bgm = Audio.Play2D("Night Changes", 1);
}

void MenuHandler::Exit()
{
	GetState<OptionScript>()->SaveOptions();

	if (Audio.IsPlaying("Night Changes"))
		Audio.StopPlaying(bgm);
}
