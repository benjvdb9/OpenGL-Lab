#include "shader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

GLuint loadShader(const char* path, GLenum shaderType)
{
	ifstream in(path, ios::in);
	string content;
	
	if(!in.is_open())
	{
		cout << "File " << path << " not found" << endl;
		return -1;
	}

	string line = "";
	while(!in.eof()) {
		getline(in, line);
		content.append(line + "\n");
	}

	in.close();
	
	const char* src = content.c_str();

	GLuint id = glCreateShader(shaderType);
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(id, infoLogLength, NULL, strInfoLog);
		
		cout << "Shader Compile Error (" << path << "): " << strInfoLog;
		delete[] strInfoLog;
	}

	return id;
}