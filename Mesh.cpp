#include "Mesh.h"

Mesh::Mesh(Program *program)
{
	this->program = program;
}

Program* Mesh::getProgram()
{
	return program;
}