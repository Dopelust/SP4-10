#include <stack>

#include "Grid.h"
#include "Cell.h"
#include "Scene\Entity\Entity.h"
#include "Scene\Scene.h"

#include "FileSystem.h"
#include "Utility.h"


#include "Partition.h"

bool Grid::Save(const char* filepath)
{
	ofstream& output = *File.BeginWriting(filepath);

	for (int y = NumberOfTilesY - 1; y >= 0; --y)
	{
		for (int x = 0; x < NumberOfTilesX; ++x)
		{
			output << GetTile(x, y)->index << ',';
		}

		output << endl;
	}

	File.EndWriting();
	return true;
}

bool Grid::Load(const char* filepath)
{
	vector<string>& lines = File.GetLines(filepath);

	if (lines.empty())
		return false;

	for (int y = NumberOfTilesY - 1; y >= 0; --y)
	{
		vector<float>& tiles = VectorStoF(ParseLine(lines[NumberOfTilesY - 1 - y], ","));

		for (int x = 0; x < NumberOfTilesX; ++x)
		{
			GetTile(x, y)->index = tiles[x];
		}
	}

	return true;
}

void Grid::Reset()
{
	for (int y = NumberOfTilesY - 1; y >= 0; --y)
	{
		for (int x = 0; x < NumberOfTilesX; ++x)
		{
			GetTile(x, y)->index = 0;
		}
	}
}

Grid::Grid(Scene* owner) : owner(owner)
{
	cell = new Cell();

	for (int i = 0; i < NumberOfPartitionsX; ++i)
	for (int j = 0; j < NumberOfPartitionsY; ++j)
		part[i][j] = new Partition(i * PartitionWidth, j * PartitionHeight);
}

Grid::~Grid()
{
	delete cell;

	for (int i = 0; i < NumberOfPartitionsX; ++i)
	for (int j = 0; j < NumberOfPartitionsY; ++j)
		delete part[i][j];
}

#include "Scene\Entity\Component\Physics\RigidBody.h"
#include "Scene\Entity\Component\Physics\BoxCollider.h"

#include <string>
#include <algorithm>
#include "CollisionQuery.h"
#include "Scene\Entity\Component\Transform.h"

void Grid::PopulateCells(Entity* ent)
{
	BoxCollider* box = ent->GetComponent<BoxCollider>();

	if (box)
	{
		box->cell = cell;

		box->part.clear();
		
		Vector3 min = box->GetMinCoord();
		Vector3 max = box->GetMaxCoord();

		min.x /= GridWidth;
		min.x *= NumberOfPartitionsX;

		max.x /= GridWidth;
		max.x *= NumberOfPartitionsX;

		min.y /= GridHeight;
		min.y *= NumberOfPartitionsY;

		max.y /= GridHeight;
		max.y *= NumberOfPartitionsY;


		for (int i = min.x; i <= max.x; ++i)
			for (int j = min.y; j <= max.y; ++j)
			{
				Partition* c = GetPartition(i, j);

				if (c)
				{
					c->Add(ent);
					box->part.push_back(c);
				}
			}
	}

	for (auto &child : ent->GetChildren())
	{
		if (child->IsActive())
			PopulateCells(child);
	}
}

vector<Partition*> Grid::GetCellsInRange(Entity * entity, float range)
{
	vector<Partition*> part;
	return part;
}

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

Partition* Grid::GetPartition(int x, int y)
{
	if (x >= 0 && y >= 0 && x < NumberOfPartitionsX && y < NumberOfPartitionsY)
		return part[x][y];

	return NULL;
}

Tile* Grid::GetTile(int x, int y)
{
	if (x >= 0 && y >= 0 && x < NumberOfTilesX && y < NumberOfTilesY)
	{
		return &cell->GetTile(x % NumberOfTilesX, y % NumberOfTilesY);
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
	for (int i = 0; i < NumberOfPartitionsX; ++i)
	for (int j = 0; j < NumberOfPartitionsY; ++j)
				part[i][j]->Reset();

	PopulateCells(owner->root);
}

void Grid::Render()
{
	cell->Draw(0, 0);
}

#include "Scene\Entity\Collision.h"

void Grid::ResolveCollisions(Entity* ent)
{
	RigidBody* rigid = ent->GetComponent<RigidBody>();

	if (rigid)
	{
		rigid->ResolveCollisions();

		BoxCollider* box = ent->GetComponent<BoxCollider>();

		if (box)
		{
			Vector3& max = box->GetMaxCoord();
			Vector3& min = box->GetMinCoord();

			if (min.x < 0 || min.y < 0 || max.x > GridWidth || max.y > GridHeight)
				ent->OnCollisionEnter(Collision());
		}
	}

	for (auto &child : ent->GetChildren())
	{
		ResolveCollisions(child);
	}
}

Vector3 Grid::GetIndex(const Vector3& position)
{
	Vector3 pos = position;
	pos.x /= GridWidth; pos.x *= NumberOfTilesX;
	pos.y /= GridHeight; pos.y *= NumberOfTilesY;

	return Vector3((int)pos.x,  (int)pos.y, (int)pos.z);
}

vector<Vector2> Grid::GetTilesWithIndex(int index)
{
	vector<Vector2> indexes;

	for (int k = 0; k < NumberOfTilesX; ++k)
	{
		for (int l = 0; l < NumberOfTilesY; ++l)
		{
			if (cell->GetTile(k, l).index == index)
			{
				indexes.push_back(Vector2(k, l));
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

	pos.x /= NumberOfTilesX;
	pos.x *= GridWidth;

	pos.y /=  NumberOfTilesY;
	pos.y *= GridHeight;

	return pos;
}