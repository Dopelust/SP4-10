#ifndef INSTANCE_H
#define INSTANCE_H

#include "Mtx44.h"
#include "Vector2.h"
#include "Vector4.h"

#include <vector>
using namespace::std;

class Mesh;
class DrawInstance
{
public:
	DrawInstance();
	DrawInstance(const Mtx44& mtx, const Vector3& color = Vector3(1, 1, 1), const Vector2& tex = Vector2());

	unsigned NumInstance() const;
	void Bind(Mesh* mesh) const;
	void Prepare(int numInstances);
	void Add(const Mtx44& mtx, const Vector3& color = Vector3(1, 1, 1), const Vector2& tex = Vector2());
	void Add(const Mtx44& mtx, const Vector4& color = Vector4(1, 1, 1), const Vector2& tex = Vector2());
	void Clear();

private:
	vector<Mtx44> modelMatrix;
	vector<Vector2> textureOffset;
	vector<Vector4> color;
};

#endif