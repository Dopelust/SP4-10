#include "Scene.h"
#include "Entity\Entity.h"
#include "Entity\EntityFactory.h"
#include "Entity\Component\GUI\Canvas.h"
#include "Entity\Component\Resolution.h"

#include "../Grid.h"
#include "../Screen.h"

#include "LUAEngine.h"

Scene* Scene::scene = NULL;

Scene::Scene(const char* filepath) : root(new Entity("Root")), canvas(new Entity("Canvas")), canvasUI(*canvas->AddComponent<CanvasUI>()), 
grid(NULL), filepath(filepath)
{
	scene = this;
	Camera::current = &camera;

	root->AddComponent<Resolution>();
	canvas->AddComponent<Resolution>();

	if (filepath && Load())
		cout << "Loaded Scene " << filepath << "." << endl;
}

Scene::~Scene()
{
	EntityFactory::GenerateEntities();
	EntityFactory::DestroyEntities();

	Camera::current = NULL;

	if (root)
		delete root;

	if (canvas)
		delete canvas;

	if (grid)
	{
		if (filepath)
			grid->Save(GetGridSavePath().c_str());

		delete grid;
	}
}

void Scene::Exit()
{
	if (filepath && Save())
		cout << "Saved Scene " << filepath << "." << endl;
}

bool Scene::CreateSpatialPartition(GridType type)
{
	if (grid)
		return false;

	switch (type)
	{
	case GRID_3D_VOXEL:
		grid = new Grid(this);
		grid->Init();
		break;
	}
}

void Scene::Update(double dt)
{
	EntityFactory::GenerateEntities();

	Screen.SetProjectionResolution(GetResolutionX(root), GetResolutionY(root));
	root->Update(dt);

	Screen.SetProjectionResolution(GetResolutionX(canvas), GetResolutionY(canvas));
	canvas->Update(dt);

	EntityFactory::DestroyEntities();

	if (grid)
	{
		grid->Update();
		grid->ResolveCollisions(root);
	}
}

void Scene::Draw()
{
	if (grid)
		grid->Render();

	root->Draw(Mtx44::GetIdentity());
	canvas->Draw(Mtx44::GetIdentity());
}

void Scene::DrawCanvas()
{
	canvas->Draw(Mtx44::GetIdentity());
}

int Scene::GetResolutionX(Entity * entity)
{
	return entity->GetComponent<Resolution>()->width;
}

int Scene::GetResolutionY(Entity * entity)
{
	return entity->GetComponent<Resolution>()->height;
}

CanvasUI& Scene::GetCanvas()
{
	return canvasUI;
}

void Scene::DrawWorld()
{
	if (grid)
		grid->Render();

	root->Draw(Mtx44::GetIdentity());
}

#include "Utility.h"

string Scene::GetCameraSavePath()
{
	return string(filepath) + "//save.lua";
}

string Scene::GetGridSavePath()
{
	return string(filepath) + "//grid.txt";
}

bool Scene::Save()
{
	//LUAEngine& lua = LUAEngine::Instance();

	//if (lua.Load(GetCameraSavePath().c_str()))
	//{
	//	lua.SetGlobalString("CAMERA_POSITION", ToString(camera.position).c_str());
	//	lua.SetGlobalString("CAMERA_ORIENTATION", ToString(camera.orientation).c_str());

	//	lua.Save(GetCameraSavePath().c_str());
	//}

	return true;
}

#include "Utility.h"

bool Scene::Load()
{
	//LUAEngine& lua = LUAEngine::Instance();

	//if (lua.Load(GetCameraSavePath().c_str()))
	//{
	//	vector<float> position = VectorStoF(ParseLine(lua.GetGlobalString("CAMERA_POSITION")));
	//	vector<float> orientation = VectorStoF(ParseLine(lua.GetGlobalString("CAMERA_ORIENTATION")));

	//	camera.position.Set(position[0], position[1], position[2]);
	//	camera.orientation.Set(orientation[0], orientation[1]);
	//	
	//	camera.Update();
	//}

	return true;
}