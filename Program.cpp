#include "Program.h"
#include "Application.h"

#include <iostream>

using namespace std;

Program::Program(GLuint vertex_shader, GLuint fragment_shader)
{
    program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	GLint status;
	glGetProgramiv (program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);

		cout << "Program link error: " << strInfoLog;
		delete[] strInfoLog;
	}

    proj_location = glGetUniformLocation(program, "Projection");
	view_location = glGetUniformLocation(program, "View");
    model_location = glGetUniformLocation(program, "Model");
}

void Program::setModelMatrix(mat4 matrix)
{
    glUniformMatrix4fv(model_location, 1, GL_FALSE, (const GLfloat*) matrix);
}

void Program::begin()
{
    bind();
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, (const GLfloat*) Application::getProjection());
	glUniformMatrix4fv(view_location, 1, GL_FALSE, (const GLfloat*) Application::getView());
}

void Program::begin(mat4 model_matrix)
{
    begin();
    setModelMatrix(model_matrix);
}

void Program::end()
{
    unbind();
}

void Program::bind()
{
    glUseProgram(program);
}

void Program::unbind()
{
    glUseProgram(0);
}

GLuint Program::getId()
{
    return program;
}