#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Computer.h"

class Sphere : public Mesh
{
	public:
	Sphere(Program *program);
	~Sphere();
	void render(mat4 model);
	void update();

	private:
	GLuint vertex_array;
	GLuint vertex_buffer;
	GLuint texture;
	GLuint texUnit;
	GLuint *indices;
	Computer *acceleration;
	Computer *cinematic;
};

#endif