#ifndef COMPUTER_H
#define COMPUTER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vmath.h"

using namespace vmath;

class Computer
{
    private:
    GLuint program;
    int workgroup_count[3];
    int workgroup_size[3];
    int workgroup_invocations;

    public:
    Computer(GLuint compute_shader);
    void setData(int index, GLuint data);
    void compute(int count_x, int count_y, int count_z);
};

#endif