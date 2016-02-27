#include "../../../../Scene.h"
#include "../../../Entity.h"
#include "../../../EntityFactory.h"
#include "../../Transform.h"

#include "Vector2.h"

#include "MenuHandler.h"
#include "MenuObject.h"

#include "MenuScript.h"
#include "OptionScript.h"
#include "LevelSelectScript.h"

#include "../../../../../SoundEngine.h"

MenuHandler::MenuHandler() : state(NULL)
{
}

MenuHandler::~MenuHandler()
{
}

void MenuHandler::Init(Entity * ent)
{
	menu = ent->AddChild("Menu")->AddComponent<MenuScript>();
	menu->menu = this;
	state = menu;

	option = ent->AddChild("Options")->AddComponent<OptionScript>();
	option->menu = this;
	option->Disappear();

	levelselect = ent->AddChild("Level Selection")->AddComponent<LevelSelectScript>();
	levelselect->menu = this;
	levelselect->Disappear();

	bgm = Audio.Play2D("Night Changes", 1);
}

void MenuHandler::Update(double dt)
{
	if (bgm->isFinished())
		Audio.Play2D("Night Changes", 1);
}

void MenuHandler::Exit()
{
	option->SaveOptions();

	if (Audio.IsPlaying("Night Changes"))
		Audio.StopPlaying(bgm);
}

void MenuHandler::Switch(MenuObject * state)
{
	if (this->state)
		this->state->Disappear();

	this->state = state;
	this->state->Appear();
}
