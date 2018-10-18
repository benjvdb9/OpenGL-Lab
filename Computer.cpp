#include "Computer.h"
#include "Application.h"

#include <iostream>

using namespace std;

Computer::Computer(GLuint compute_shader)
{
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &workgroup_count[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &workgroup_count[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &workgroup_count[2]);

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &workgroup_size[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &workgroup_size[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &workgroup_size[2]);

    glGetIntegerv (GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &workgroup_invocations);

    program = glCreateProgram();
	glAttachShader(program, compute_shader);
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
}

void Computer::setData(int index, GLuint data)
{
    glUseProgram(program);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, data);
    glUseProgram(0);
}

void Computer::compute(int count_x, int count_y, int count_z)
{
    glUseProgram(program);
    glDispatchCompute(count_x, count_y, count_z);
    glUseProgram(0);
}