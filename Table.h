#ifndef TABLE_MESH_H
#define TABLE_MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"

class Table : public Mesh
{
	public:
	Table(Program *program);
	void render(mat4 model);

	private:
	GLuint vertex_array;
};

#endif