// Author: Quentin Lurkin

#include "Application.h"
#include "Table.h"
#include "Sphere.h"
#include "Sheet.h"
#include "Object.h"
#include "Program.h"

#include <iostream>

using namespace std;

class MyApplication : public Application
{
	private:
	Sphere *sphere;
	Sheet *sheet;	
	Object *root;
	Object *root2;
	Program *program;

	public:
	void setup()
	{
		GLuint vertex_shader, fragment_shader;
		GLint view_location;

		// Chargement des shaders
		fragment_shader = loadShader("shader.frag", GL_FRAGMENT_SHADER);
		vertex_shader = loadShader("shader.vert", GL_VERTEX_SHADER);

		// Creation du pipeline 
		program = new Program(vertex_shader, fragment_shader);

		// Create a Mesh instance
		sphere = new Sphere(program);

		sheet = new Sheet(program);

		// Create an Object
		root = new Object(sphere, vec3(0, 0, 0), mat4::identity());
		root2 = new Object(sheet, vec3(0, 0, 0), mat4::identity());
	}

	void update()
	{
		// Update rotation of the object
		root->setRotation(rotate((float) glfwGetTime()*20, 0.0f, 0.0f, 1.0f));
		//sheet->update();
	}

	void render()
	{
		mat4 projection, view, model;
		
		// Création des matrice View et Projection
		float ratio;
		ratio = getWidth() / (float) getHeight();
		projection = perspective(30.f, ratio, 0.1f, 10);
		view = lookat(vec3(0, -2, 2), vec3(0, 0, 0), vec3(0, 0, 1));
		model = mat4::identity();

		setProjection(projection);
		setView(view);

		root->render(model);
		root2->render(model);
	}

	void teardown()
	{
		delete root;
		delete root2;
		delete sphere;
		delete sheet;
		delete program;
	}
};

int main(void)
{
	return MyApplication().run();
}

//TODO: GL Error managment, Object séparation, Log, Exception, Renderable, Updatable, Object Tree, Check comment