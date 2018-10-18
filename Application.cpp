#include "Application.h"
#include <iostream>

using namespace std;

mat4 Application::projection = mat4::identity();
mat4 Application::view = mat4::identity();

static void error_callback(int error, const char* description)
{
	cout << "Error: " << description << endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int Application::run()
{
	GLFWwindow* window;

	cout << "Hello OpenGL" << endl;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		return EXIT_FAILURE;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1024, 768, "OpenGL Lab", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << endl;
		return EXIT_FAILURE;
	}

	glfwSwapInterval(1);
	glPointSize(4);
	glDisable(GL_CULL_FACE);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0, 1.0);

	glClearColor(0.7, 0.7, 0.7, 1.0);
	glClearDepth(1.0f);

	setup();

	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update();
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		GLuint error = glGetError();
		if(error != GL_NO_ERROR)
		{
			cout << "OpenGL ERROR: " << error << endl;
		}
	}

	teardown();

	glfwDestroyWindow(window);

	glfwTerminate();

	return EXIT_SUCCESS;
}

int Application::getWidth()
{
	return width;
}

int Application::getHeight()
{
	return height;
}

void Application::setProjection(mat4 matrix)
{
	projection = matrix;
}

mat4 Application::getProjection()
{
	return projection;
}

void Application::setView(mat4 matrix)
{
	view = matrix;
}

mat4 Application::getView()
{
	return view;
}
