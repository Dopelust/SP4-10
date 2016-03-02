#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"

#include <string>
using namespace::std;

#define Canvas Scene::scene->GetCanvas()

class CanvasUI;
class Entity;
class Grid;
class Scene
{
public:
	static Scene* scene;

	Scene(const char* filepath);
	~Scene();
	void Exit();

	Camera camera;

	enum GridType
	{
		GRID_3D_VOXEL,
	};
	bool CreateSpatialPartition(GridType type);

	Grid* grid;

	void Update(double dt);
	void Draw();

	void DrawWorld();
	void DrawCanvas();

	int GetResolutionX(Entity* entity);
	int GetResolutionY(Entity* entity);

	Entity* canvas;
	CanvasUI& GetCanvas();

	Entity* root;

	string GetCameraSavePath();
	string GetGridSavePath();

private:
	const char* filepath;

	bool Save();
	bool Load();

	CanvasUI& canvasUI;
};

#endif