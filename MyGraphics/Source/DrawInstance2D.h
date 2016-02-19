#pragma once

#include "Mtx44.h"
#include "Vector2.h"
#include "Vector4.h"

#include <vector>
using namespace::std;

class Mesh2D;
class DrawInstance2D
{
public:
	DrawInstance2D();
	DrawInstance2D(const Mtx44& mtx, const Vector3& color = Vector3(1, 1, 1), const Vector4& tex = Vector4());

	unsigned NumInstance() const;
	void Bind(Mesh2D* mesh) const;
	void Prepare(int numInstances);
	void Add(const Mtx44& mtx, const Vector3& color = Vector3(1, 1, 1), const Vector4& tex = Vector4());
	void Add(const Mtx44& mtx, const Vector4& color = Vector4(1, 1, 1), const Vector4& tex = Vector4());
	void Clear();

private:
	vector<Mtx44> modelMatrix;
	vector<Vector4> textureOffset;
	vector<Vector4> color;
};