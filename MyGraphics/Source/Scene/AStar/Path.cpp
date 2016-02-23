#include "Path.h"

int Path::GetPathLength()
{
	return path.size();
}

Vector2 Path::GetPath(int index)
{
	if (path.size() > index)
		return path[index];

	return Vector2();
}

void Path::AddToPath(const Vector2 & path)
{
	this->path.push_back(path);
}
