#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Vector.h"
#include "Mesh.h"
#include "Graphics.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

#define  N_POINTS 730



class graphics3D : public olc::PixelGameEngine
{
public:
	graphics3D()
	{
		sAppName = "3d Graphics";
	}
public:
	
	std::vector<triangle_t> trangles_to_render;
	vec3_t camera_position = { 0,0, 0 };
	

	float fov_factor = 128;

public:
	vec2_t project(vec3_t point)
	{
		vec2_t projected_point = { (fov_factor * point.x) / point.z, (fov_factor * point.y) / point.z };
		return projected_point;
	}

public:

	bool OnUserCreate() override
	{
		load_obj_file_data("./assets/cube.obj");

		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		mesh.rotation.x += 0.5f * fElapsedTime;
		mesh.rotation.y += 0.5f * fElapsedTime;
		mesh.rotation.z += 0.5f * fElapsedTime;
		Clear(olc::BLACK);

		if (GetKey(olc::UP).bHeld)
		{
			camera_position.z += 0.01f;
		}

		if (GetKey(olc::DOWN).bHeld)
		{
			camera_position.z -= 0.01f;
		}

		trangles_to_render.clear();
		
		int num_faces = mesh.faces.size();

		for (int i = 0; i < num_faces; i++)
		{
			face_t mesh_face = mesh.faces[i];
			vec3_t face_vertices[3];

			face_vertices[0] = mesh.vertices[mesh_face.a - 1];
			face_vertices[1] = mesh.vertices[mesh_face.b - 1];
			face_vertices[2] = mesh.vertices[mesh_face.c - 1];

		
			

			vec3_t transformed_vertices[3];
			for (int j = 0; j < 3; j++)
			{
				vec3_t transformed_vertex = face_vertices[j];
				transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
				transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
				transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);

				transformed_vertex.z += 3;

				transformed_vertices[j] = transformed_vertex;
			}

			//back face culling
			vec3_t vector_a = transformed_vertices[0];
			vec3_t vector_b = transformed_vertices[1];
			vec3_t vector_c = transformed_vertices[2];

			vec3_t vector_ab = vec3_sub(vector_b, vector_a);
			vec3_t vector_ac = vec3_sub(vector_c, vector_a);

			vec3_t normal = vec3_cross(vector_ab, vector_ac);

			vec3_t camera_ray = vec3_sub(camera_position, vector_a);

			float dot_normal_camera = vec3_dot(normal, camera_ray);

			if (dot_normal_camera < 0)
			{
				continue;
			}


			triangle_t projected_triangle;


			for (int j = 0; j < 3; j++)
			{
				vec2_t projected_point = project(transformed_vertices[j]);

				projected_point.x += (ScreenWidth() / 2);
				projected_point.y += (ScreenHeight() / 2);


				projected_triangle.points[j] = projected_point;

			}

				trangles_to_render.push_back(projected_triangle);
			
		}
		
		int t_length = trangles_to_render.size();

		for (int i = 0; i < t_length; i++)
		{
			triangle_t triangle = trangles_to_render[i];
			draw_rect(this, triangle.points[0].x, triangle.points[0].y, 4, 4, olc::CYAN );
			draw_rect(this,triangle.points[1].x, triangle.points[1].y, 4, 4, olc::CYAN);
			draw_rect(this,triangle.points[2].x, triangle.points[2].y, 4, 4, olc::CYAN);
			draw_triangle(
				this,
				triangle.points[0].x,
				triangle.points[0].y,
				triangle.points[1].x,
				triangle.points[1].y,
				triangle.points[2].x,
				triangle.points[2].y,
				olc::GREEN
				);
		}
		

		return true;
	}

	bool OnUserDestroy() override
	{
		

		return true;
	}
};


int main()
{

	graphics3D demo;
	if (demo.Construct(WINDOW_WIDTH, WINDOW_HEIGHT, 1, 1))
	{
		demo.Start();
	}
}