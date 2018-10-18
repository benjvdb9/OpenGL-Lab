#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint loadShader(const char* path, GLenum shaderType);

#endif