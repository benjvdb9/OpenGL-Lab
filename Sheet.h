#ifndef SHEET_MESH_H
#define SHEET_MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Computer.h"

class Sheet : public Mesh
{
	public:
	Sheet(Program *program);
	~Sheet();
	void render(mat4 model);
	void update();

	private:
	GLuint vertex_array;
	GLuint vertex_buffer;
	GLuint texture;
	GLuint texUnit;
	GLuint *indices;
	Computer *physics;
	Computer *cinematic;
	Computer *acceleration;
};

#endif