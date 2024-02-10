#include "Mesh.h"

mesh_t mesh;

vec3_t cube_vertices[N_CUBE_VERTICES] =
{
	{-1, -1, -1},
	{-1,  1, -1},
	{ 1,  1, -1},
	{ 1, -1, -1},
	{ 1,  1,  1},
	{ 1,  -1,  1},
	{-1,  1,  1},
	{-1, -1,  1}
};

face_t cube_faces[N_CUBE_FACES] =
{
	//front
	{1, 2 , 3},
	{1, 3 , 4},
	//right
	{4, 3, 5},
	{4, 5 ,6},
	//back
	{6, 5 , 7},
	{6, 7, 8},
	//left
	{8, 7, 2},
	{8, 2 , 1},
	//top
	{2,7,5},
	{2,5,3},
	//bottom
	{6,8,1},
	{6,1,4}

};

void load_cube_mesh_data()
{
	for (int i = 0; i < N_CUBE_VERTICES; i++)
	{
		vec3_t cube_vertex = cube_vertices[i];
		mesh.vertices.push_back(cube_vertex);
	}

	for (int i = 0; i < N_CUBE_FACES; i++)
	{
		face_t cube_face = cube_faces[i];
		mesh.faces.push_back(cube_face);
	}

	mesh.rotation = { 0,0,0 };
}

void load_obj_file_data(const char* filename)
{
	FILE* file;
	file = fopen(filename, "r");
	char line[1024];
	
	while (fgets(line, 1024, file) != nullptr)
	{
		if (strncmp(line, "v ", 2) == 0)
		{
			vec3_t vertex;
			sscanf_s(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			mesh.vertices.push_back(vertex);
		}
	
		if (strncmp(line, "f ", 2) == 0)
		{
			
				face_t face;
				sscanf_s(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &face.a, &face.b, &face.c);
	
			mesh.faces.push_back(face);
		}
	}

	
}
