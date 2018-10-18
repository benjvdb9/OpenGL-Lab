#include "Triangle.h"

#include <iostream>
#include "shader.h"
#include "texture.h"

using namespace std;

Triangle::Triangle(Program *program) : Mesh(program)
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
	
	Vertex vertices[3];

	vertices[0].position = vec3(-0.6f, -0.4f, 0.f);
	vertices[1].position = vec3(0.6f, -0.4f, 0.f);
	vertices[2].position = vec3(0.f, 0.6f, 0.f);

	for(int i=0; i<3; i++)
	{
		vertices[i].velocity = vec3(0.f, 0.0f, 0.f);
		vertices[i].acceleration = vec3(0.f, 0.0f, 0.f);
		vertices[i].normal = vec3(0.f, 0.f, 1.f);
		vertices[i].tangent = vec3(1.f, 0.f, 0.f);
	}
	
	vertices[0].texture = vec2(0.f, 0.f);
	vertices[1].texture = vec2(1.f, 0.f);
	vertices[2].texture = vec2(0.5f, 1.f);
	// {
	// 	{vec3(-0.6f, -0.4f, 0.f), 1.f, vec3(0.f, 0.f, 0.f), 1.f, vec3(0.f, 0.f, 1.f), 1.f, vec3(1.f, 0.f, 0.f), 1.f, vec2(0.f, 0.f), 1.f, 1.f },
	// 	{vec3(0.6f, -0.4f, 0.f), 1.f, vec3(0.f, 0.f, 0.f), 1.f, vec3(0.f, 0.f, 1.f), 1.f, vec3(1.f, 0.f, 0.f), 1.f, vec2(1.f, 0.f), 1.f, 1.f },
	// 	{vec3(0.f, 0.6f, 0.f), 1.f, vec3(0.f, 0.f, 0.f), 1.f, vec3(0.f, 0.f, 1.f), 1.f, vec3(1.f, 0.f, 0.f), 1.f, vec2(0.5f, 1.f), 1.f, 1.f }
	// };

	// 
	indices = new GLuint[3];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 3, indices, GL_STATIC_DRAW);

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

	GLuint acceleration_shader = loadShader("acceleration.comp", GL_COMPUTE_SHADER);
	acceleration = new Computer(acceleration_shader);
	acceleration->setData(1, vertex_buffer);

	GLuint cinematic_shader = loadShader("cinematic.comp", GL_COMPUTE_SHADER);
	cinematic = new Computer(cinematic_shader);
	cinematic->setData(1, vertex_buffer);
}

Triangle::~Triangle()
{
	delete[] indices;
	delete acceleration;
	delete cinematic;
}

void Triangle::update()
{
	acceleration->compute(1, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	cinematic->compute(1, 1, 1);
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
}

void Triangle::render(mat4 model)
{
	getProgram()->begin(model);

	// Selection du VertexArray
	glBindVertexArray(vertex_array);

	// activer la texture
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Affichage des 3 1ers sommets en utilisant des triangles.
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*) 0);

	getProgram()->end();
}