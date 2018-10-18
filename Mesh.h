#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Program.h"

#include "vmath.h"

using namespace vmath;

class Mesh
{
	public:
	Mesh(Program *program);
	Program* getProgram();
	virtual void render(mat4 model) = 0;

	private:
	Program *program;
};

#endif