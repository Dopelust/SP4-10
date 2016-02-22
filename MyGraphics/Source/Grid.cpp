#include <stack>

#include "Grid.h"
#include "Cell.h"
#include "Scene\Entity\Entity.h"
#include "Scene\Scene.h"

#include "FileSystem.h"
#include "Utility.h"

bool Grid::Save(const char* filepath)
{
	FileSystem* file = FileSystem::Instance();

	ofstream& output = *file->BeginWriting(filepath);

	for (int y = NumberOfTilesY - 1; y >= 0; --y)
	{
		for (int x = 0; x < NumberOfTilesX; ++x)
		{
			output << GetCell(0, 0)->GetTile(x, y).index << ',';
		}

		output << endl;
	}

	return true;
}

bool Grid::Load(const char* filepath)
{
	FileSystem* file = FileSystem::Instance();

	vector<string>& lines = file->GetLines(filepath);

	if (lines.empty())
		return false;

	for (int y = NumberOfTilesY - 1; y >= 0; --y)
	{
		vector<float>& tiles = VectorStoF(ParseLine(lines[NumberOfTilesY - 1 - y], ","));

		for (int x = 0; x < NumberOfTilesX; ++x)
		{
			GetCell(0, 0)->Place(x, y, tiles[x]);
		}
	}

	return true;
}

Grid::Grid(Scene* owner) : owner(owner)
{
	for (int i = 0; i < NumberOfCellsX; ++i)
	for (int j = 0; j < NumberOfCellsY; ++j)
		cell[i][j] = new Cell();
}

Grid::~Grid()
{
	for (int i = 0; i < NumberOfCellsX; ++i)
	for (int j = 0; j < NumberOfCellsY; ++j)
		delete cell[i][j];
}

#include "Scene\Entity\Component\Physics\RigidBody.h"
#include "Scene\Entity\Component\Physics\BoxCollider.h"

#include <string>
void Grid::PopulateCells(Entity* ent)
{
	BoxCollider* box = ent->GetComponent<BoxCollider>();

	if (box)
	{
		Vector3 min = GetIndex(box->GetMinCoord()) / NumberOfTilesX;
		Vector3 max = GetIndex(box->GetMaxCoord()) / NumberOfTilesY;

		box->cells.clear();

		for (int i = min.x; i <= max.x; ++i)
			for (int j = min.y; j <= max.y; ++j)
				{
					Cell* c = GetCell(i, j);

					if (c)
					{
						c->Add(ent);
						box->cells.push_back(c);
					}
				}
	}

	for (auto &child : ent->GetChildren())
	{
		if (child->IsActive())
			PopulateCells(child);
	}
}

vector<Cell*> Grid::GetCellsInRange(Entity * entity, float range)
{
	vector<Cell*> cell;
	return cell;
}

#include <algorithm>
#include "CollisionQuery.h"
#include "Scene\Entity\Component\Transform.h"

vector<Entity*> Grid::GetEntitiesInRange(Entity * entity, float range)
{
	Vector3& position = entity->transform->GetPosition();

	vector<Entity*> entityList;

	for (auto& cell : GetCellsInRange(entity, range))
	{
		for (auto& ent : cell->GetEntities())
		{
			if (ent == entity)
				continue;

			if (CollisionQuery::Test(ent->GetComponent<BoxCollider>(), position, range))
			{
				if (find(entityList.begin(), entityList.end(), ent) == entityList.end())
					entityList.push_back(ent);
			}
		}
	}

	return entityList;
}

Cell * Grid::GetCell(int x, int y)
{
	if (x >= 0 && y >= 0 && x < NumberOfCellsX && y < NumberOfCellsY)
		return cell[x][y];

	return NULL;
}

Tile* Grid::GetTile(int x, int y)
{
	if (x >= 0 && y >= 0 && x < NumberOfCellsX * NumberOfTilesX && y < NumberOfCellsY * NumberOfTilesY)
	{
		return &GetCell(x / (NumberOfCellsX * NumberOfTilesX), y / (NumberOfCellsY * NumberOfTilesY))->GetTile(x % NumberOfTilesX, y % NumberOfTilesY);
	}

	return NULL;
}

#include "CollisionQuery.h"
#include "Scene\Entity\Component\Transform.h"

void Grid::Init()
{
}

void Grid::Update()
{
	for (int i = 0; i < NumberOfCellsX; ++i)
	for (int j = 0; j < NumberOfCellsY; ++j)
				cell[i][j]->Reset();

	PopulateCells(owner->root);
}

void Grid::Render()
{
	for (int i = 0; i < NumberOfCellsX; ++i)
	for (int j = 0; j < NumberOfCellsY; ++j)
		cell[i][j]->Draw(i, j);
}

#include "Scene\Entity\Collision.h"

void Grid::ResolveCollisions(Entity* ent)
{
	RigidBody* rigid = ent->GetComponent<RigidBody>();

	if (rigid)
	{
		rigid->ResolveCollisions();
	}

	for (auto &child : ent->GetChildren())
	{
		ResolveCollisions(child);
	}
}

Vector3 Grid::GetIndex(const Vector3& position)
{
	Vector3 pos = position;
	pos.x /= GridWidth; pos.x *= NumberOfCellsX * NumberOfTilesX;
	pos.y /= GridHeight; pos.y *= NumberOfCellsY * NumberOfTilesY;

	return Vector3((int)pos.x,  (int)pos.y, (int)pos.z);
}

vector<Vector2> Grid::GetTilesWithIndex(int index)
{
	vector<Vector2> indexes;

	for (int i = 0; i < NumberOfCellsX; ++i)
	{
		for (int j = 0; j < NumberOfCellsY; ++j)
		{
			for (int k = 0; k < NumberOfTilesX; ++k)
			{
				for (int l = 0; l < NumberOfTilesY; ++l)
				{
					if (cell[i][j]->GetTile(k, l).index == index)
					{
						indexes.push_back(Vector2(i * NumberOfTilesX + k, j * NumberOfTilesY + l));
					}
				}
			}
		}
	}

	return indexes;
}

Vector3 Grid::GetPosition(const Vector2& index)
{
	Vector3 pos;
	pos.Set(index.x, index.y, 0);

	pos.x += 0.5f;
	pos.y += 0.5f;

	pos.x /= NumberOfCellsX * NumberOfTilesX;
	pos.x *= GridWidth;

	pos.y /= NumberOfCellsY * NumberOfTilesY;
	pos.y *= GridHeight;

	return pos;

	/*pos.x /= GridWidth; pos.x *= NumberOfCellsX * NumberOfTilesX;
	pos.y /= GridHeight; pos.y *= NumberOfCellsY * NumberOfTilesY;

	return Vector3((int)(pos.x + 0.5f), (int)(pos.y + 0.5f), (int)(pos.z + 0.5f));*/
}