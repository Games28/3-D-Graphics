#ifndef MESH_H
#define MESH_H
#include "Vector.h"
#include "triangle.h"
#include <string>
#include <vector>

#define N_CUBE_VERTICES 8

extern vec3_t cube_vertices[N_CUBE_VERTICES];



#define N_CUBE_FACES (6 * 2)
extern face_t cube_faces[N_CUBE_FACES];


typedef struct
{
std::vector<vec3_t> vertices;
std::vector<face_t> faces;
	vec3_t rotation;

}mesh_t;

extern mesh_t mesh;


void load_cube_mesh_data();
void load_obj_file_data(const char* filename);
#endif // !MESH_H


