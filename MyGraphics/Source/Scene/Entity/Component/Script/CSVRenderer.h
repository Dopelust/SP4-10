#pragma once

#include "../Graphic2D.h"

#include <vector>
using namespace::std;

class Transform;
class Spritesheet;
class CSVRenderer : public Graphic2D
{
public:
	CSVRenderer();
	~CSVRenderer();

	void Init(Entity* ent);

	void SetIndividualSize(int width, int height);

	void UploadCSV(const char* filepath);
	void UpdateSize();

	void SetSpritesheet(Spritesheet* sprite);

protected:
	Transform* transform;
	Spritesheet* sprite;
	vector<vector<int>> csv;

	float width, height;
	void Draw(const Mtx44& parent);
	void DrawOcclusion(const Mtx44& mtx, int orientation);
};