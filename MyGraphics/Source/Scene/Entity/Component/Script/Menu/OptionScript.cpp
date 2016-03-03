#include "OptionScript.h"

OptionScript::OptionScript()
{
}

OptionScript::~OptionScript()
{
}

#include "../../../../Scene.h"
#include "../../../Entity.h"
#include "../../../EntityFactory.h"
#include "../../Transform.h"

#include "../../GUI/Button.h"
#include "../../GUI/Slider.h"

#include "Vector2.h"

#include "LUAEngine.h"
#include "../../../../../SoundEngine.h"
#include "../../TextRenderer2D.h"

void OptionScript::Init(Entity * ent)
{
	StateObject::Init(ent);

	Entity* entity = ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 200), "BACK", 400, Vector3(0.7f, 0.7f, 0)));
	back = entity->GetComponent<Button>();

	Entity* SmoothSlide = ent->AttachChild(EntityFactory::CreateSlider(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5, Scene::scene->GetResolutionY(Scene::scene->canvas)*0.45f), Vector2(400, 12), "SFX", 0, LUA.GetGlobalNumber("SFX_VOLUME"), 100, true));
	sfx = SmoothSlide->GetChild("Slider")->GetComponent<Slider>();

	SmoothSlide->AttachChild(EntityFactory::CreateCheckbox(Vector2(-180, -24), 16, 2, "Mute"));

	SmoothSlide = ent->AttachChild(EntityFactory::CreateSlider(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5, Scene::scene->GetResolutionY(Scene::scene->canvas)*0.6f), Vector2(400, 12), "BGM", 0, LUA.GetGlobalNumber("BGM_VOLUME"), 100, true));
	bgm = SmoothSlide->GetChild("Slider")->GetComponent<Slider>();

	SmoothSlide->AttachChild(EntityFactory::CreateCheckbox(Vector2(-180, -24), 16, 2, "Mute"));

	Audio.SetVolume(bgm->GetValue() * 0.01f);

	target.Set(Scene::scene->GetResolutionX(Scene::scene->canvas), 0);
	transform->Position() = target.GetVector3();

	rate = 16;
}

#include "MenuHandler.h"
#include "MenuScript.h"


void OptionScript::Update(double dt)
{
	StateObject::Update(dt);

	if (back->IsState())
		menu->Pop();

	if (bgm->ValueChanged())
		Audio.SetVolume(bgm->GetValue() * 0.01f);
}

void OptionScript::SaveOptions()
{
	//if (LUA.Load("Data//properties.lua"))
	//{
	//	LUA.SetGlobalNumber("BGM_VOLUME", bgm->GetValue());
	//	LUA.SetGlobalNumber("SFX_VOLUME", sfx->GetValue());

	//	LUA.Save("Data//properties.lua");
	//}
}
