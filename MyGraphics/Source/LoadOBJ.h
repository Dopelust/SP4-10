#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include <vector>
#include "Vertex.h"
#include "Vector2.h"
#include "Vector3.h"

bool LoadOBJ(
	const char *file_path, 
	std::vector<Vector3> & out_vertices,
	std::vector<Vector2> & out_uvs,
	std::vector<Vector3> & out_normals
);

void IndexVBO(
	std::vector<Vector3> & in_vertices,
	std::vector<Vector2> & in_uvs,
	std::vector<Vector3> & in_normals,

	std::vector<unsigned> & out_indices,
	std::vector<Vertex> & out_vertices
);

#endif