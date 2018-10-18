#include "Sphere.h"

#include <iostream>
#include <math.h>
#include "shader.h"
#include "texture.h"
#define PI 3.14159265

using namespace std;

Sphere::Sphere(Program *program) : Mesh(program)
{   
	// Définition des VertexData
	struct Vertex
	{
		vec3 position;
		float p1;
		vec3 velocity;
		float p2;
		vec3 acceleration;
		float p3;
		vec3 normal;
		float p4;
		vec3 tangent;
		float p5;
		vec2 texture;
		float p6, p7;
	};
	
	Vertex vertices[2160];

	int n;
	float x, y, z, O, Y;
	for(int phi=0; phi<12; phi++)
	{
		for(int theta=0; theta<180; theta++)
		{
			n = phi*180 + theta;
			O = (theta - 90) * PI / 180;
			Y = phi * PI * 30 /180;

			x = (1 * cos(O) * cos(Y));
			y = (1 * cos(O) * sin(Y));
			z = (1 * sin(O));

			vertices[n].position = vec3(x, y, z);
		}		
	}

	for(int i=0; i<2160; i++)
	{
		vertices[i].velocity = vec3(0.f, 0.0f, 0.f);
		vertices[i].acceleration = vec3(0.f, 0.0f, 0.f);
		vertices[i].normal = vec3(0.f, 0.f, 1.f);
		//vertices[i].texture = vec2(0.f, 0.f);
	}

	x, y = 0, 0;
	for(int i=0; i<2160; i++)
	{
		for(int j=0; j<180; j++)
		{
			vertices[i].texture = vec2(x, y);
			y += 1 / 180;
		}
		x += 2 / 12
	}

	indices = new GLuint[2160];
	for(int i=0; i<2160; i++)
	{
		indices[i] = i;
	}

	GLint vpos_location, vtex_location, tex_location, vnor_location;

	// Creation de la texture
	texture = createTexture("textures/Rock_wall/diffuse.png");

	// Récupération des "location" des variable "vPos" et "vCol" du pipeline
	vpos_location = glGetAttribLocation(program->getId(), "vPos");
	vtex_location = glGetAttribLocation(program->getId(), "vTex");
	vnor_location = glGetAttribLocation(program->getId(), "vNorm");
	tex_location = glGetUniformLocation(program->getId(), "Tex");

	// Création du VertexArray
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	// Définition du vertexBuffer
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertex_buffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_COPY);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

	GLuint index_buffer;
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 2160, indices, GL_STATIC_DRAW);

	program->bind();

	// Association des composantes des VertexData à la variable "vPos" du pipeline
	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) 0);

	// Association des composantes des VertexData à la variable "vNorm" du pipeline
	glEnableVertexAttribArray(vnor_location);
	glVertexAttribPointer(vnor_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) (sizeof(float) * 12));

	// Association des composantes suivantes des VertexData à la variable "vTex" du pipeline  
	glEnableVertexAttribArray(vtex_location);
	glVertexAttribPointer(vtex_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) (sizeof(float) * 20));

	// Association de la texture à la variable "Tex"
	texUnit = 1;
	glUniform1i(tex_location, texUnit);

	program->unbind();
}

Sphere::~Sphere()
{
	delete[] indices;
}

void Sphere::render(mat4 model)
{
	getProgram()->begin(model);

	// Selection du VertexArray
	glBindVertexArray(vertex_array);

	// activer la texture
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, texture);

	int ind;
	for(int i=0; i<12; i++)
	{
		ind = i*180*sizeof(GLuint);
		glDrawElements(GL_LINE_STRIP, 180, GL_UNSIGNED_INT, (void*) ind);
	}

	getProgram()->end();
}