#include "MenuState.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "Assets.h"

#include "InputHandler.h"

#include <iostream>
using namespace::std;

MenuState& MenuState::Instance()
{
	static MenuState state;
	return state;
}

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

#include "Scene\Scene.h"
#include "Scene\Entity\Entity.h"
#include "Scene\Entity\EntityFactory.h"

#include "Scene\Entity\Component\Script\Menu\InteractiveBackground.h"
#include "Scene\Entity\Component\Script\Menu\MenuHandler.h"

#include "Screen.h"

#include "Scene\Enemy\EnemyDatabase.h"

void MenuState::Init()
{
	glClearColor(0.2, 0.2, 0.2, 1);

	scene = new Scene(NULL);

	EnemyDatabase::Init("jelly");

	Entity* entity = scene->canvas->AddChild("Main Menu");
	menu = entity->AddComponent<MenuHandler>();

	entity = scene->canvas->AddChild("Background");
	entity->AddComponent<InteractiveBackground>();

	Resume();
}

void MenuState::Exit()
{
	menu->Exit();

	if (scene)
	{
		scene->Exit();

		delete scene;
		scene = NULL;
	}
}

void MenuState::Update(float dt)
{
	scene->Update(dt);
}

#include "FontManager.h"
#include "Mesh2D.h"
#include "Texture.h"

void MenuState::Render()
{
	Graphics.Start();

	Graphics.ForwardPass(0);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	scene->DrawWorld();
	Graphics.Render2D("2D", scene->GetResolutionX(scene->root), scene->GetResolutionY(scene->root), false);
	Texture* texture = Graphics.BlurCurrentOutput(8);

	Graphics.ForwardPass(0);

	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	Graphics.RenderOnScreen(texture);

	scene->DrawCanvas();
	Graphics.Render2D("2D", scene->GetResolutionX(scene->canvas), scene->GetResolutionY(scene->canvas), true);

	Graphics.RenderOnScreen(Resource.GetTexture("Vignette"));

	Graphics.ForwardPass(1);

	Graphics.Finish();
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
	Input.ShowCursor();
	Scene::scene = scene; 
	Camera::current = &scene->camera;
}