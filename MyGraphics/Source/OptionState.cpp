#include "OptionState.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "Assets.h"

#include "InputHandler.h"

#include <iostream>
using namespace::std;

OptionState& OptionState::Instance()
{
	static OptionState state;
	return state;
}

OptionState::OptionState()
{
}

OptionState::~OptionState()
{
}

#include "Scene\Scene.h"
#include "Scene\Entity\Entity.h"
#include "Scene\Entity\EntityFactory.h"

#include "Scene\Entity\Component\GUI\Button.h"
#include "Scene\Entity\Component\GUI\Slider.h"

#include "Screen.h"

#include "SoundEngine.h"

void OptionState::Init()
{
	glClearColor(0.2, 0.2, 0.2, 1);
	
	if (!Audio.IsPlaying("Juan"))
		datsound = Audio.Play2D("Juan");

	scene = new Scene(NULL);

	Entity* entity = EntityFactory::GenerateButton(Vector2(scene->GetResolutionX(scene->canvas) * 0.5f, 200), Vector2(200, 50), NULL, Vector3(0.5f, 0.5f, 0.5f));
	entity->AttachChild(EntityFactory::CreateTextGUI(Vector2(), "RETURN", 128));
	back = entity->GetComponent<Button>();

	entity = scene->root->AttachChild(EntityFactory::CreateGraphic(
		Vector2(scene->GetResolutionX(scene->canvas) * 0.5f, scene->GetResolutionY(scene->canvas) * 0.5f),
		Vector2(scene->GetResolutionX(scene->canvas), scene->GetResolutionY(scene->canvas)),
		Resource.GetTexture("NightChanges"),
		Vector4(1, 1, 1, 1.0f)
		));

	Entity* SmoothSlide = EntityFactory::GenerateSlider(Vector2(scene->GetResolutionX(scene->canvas) * 0.5, scene->GetResolutionY(scene->canvas)*0.45f), Vector2(400, 50), "SFX", NULL, 0, 100, 100, true);
	slider = SmoothSlide->GetChild("Slider")->GetComponent<Slider>();

	SmoothSlide->AttachChild(EntityFactory::CreateCheckbox(Vector2(-170, -50), 24, 4, "Mute", &sfx));

	SmoothSlide = EntityFactory::GenerateSlider(Vector2(scene->GetResolutionX(scene->canvas) * 0.5, scene->GetResolutionY(scene->canvas)*0.6f), Vector2(400, 50), "BGM", NULL, 0, 100, 100, true);
	slider = SmoothSlide->GetChild("Slider")->GetComponent<Slider>();

	SmoothSlide->AttachChild(EntityFactory::CreateCheckbox(Vector2(-170, -50), 24, 4, "Mute", &bgm));

	Resume();
}

void OptionState::Exit()
{
	if (scene)
	{
		scene->Exit();

		delete scene;
		scene = NULL;
	}

	Audio.StopPlaying(datsound);
}

void OptionState::Update(float dt)
{
	if (!bgm)
		Audio.SetVolume(slider->GetValue() * 0.01f);
	else
		Audio.SetVolume(0);

	scene->Update(dt);
}

#include "MenuState.h"

void OptionState::HandleEvents()
{
	if (back->IsState())
		Engine.ChangeState(&MenuState::Instance());
}

#include "FontManager.h"

void OptionState::Render()
{
	Graphics.Start();

	Graphics.ForwardPass(0);

	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	scene->DrawWorld();
	Graphics.Render2D("2D", scene->GetResolutionX(scene->root), scene->GetResolutionY(scene->root), false);

	scene->DrawCanvas();
	Graphics.Render2D("2D", scene->GetResolutionX(scene->canvas), scene->GetResolutionY(scene->canvas), true);

	Graphics.ForwardPass(1);

	Graphics.Finish();
}

void OptionState::Pause()
{
}

void OptionState::Resume()
{
	Input.ShowCursor();
	Scene::scene = scene;
}