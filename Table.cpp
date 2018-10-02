#include "Table.h"
#include "texture.h"

#include <iostream>

using namespace std;

Table::Table(GLuint program) : Mesh(program)
{   
    // Définition des VertexData
    const struct
    {
        float x, y, z;
        float xn, yn, zn;
        float u, v;
    } vertices[4] =
    {
        { -0.5f, -0.5f, 0.f, 0.f, 0.f, 1.0f, 0.f, 0.f },
        { +0.5f, -0.5f, 0.f, 0.f, 0.f, 1.0f, 1.f, 0.f },
        { +0.5f, +0.5f, 0.f, 0.f, 0.f, 1.0f, 1.f, 1.f },
        { -0.5f, +0.5f, 0.f, 0.f, 0.f, 1.0f, 0.f, 1.f }
    };

    GLint vpos_location, vnor_location, vtex_location, tex_location;
    GLuint texture, sampler, texUnit;

    texture = createTexture("textures/Rock_wall/diffuse.png");

    // Récupération des "location" des variable "vPos" et "vCol" du pipeline
    vpos_location = glGetAttribLocation(program, "vPos");
    vnor_location = glGetAttribLocation(program, "vNor");
    vtex_location = glGetAttribLocation(program, "vTex");
    tex_location = glGetUniformLocation(program, "Tex");

    // Création du VertexArray
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    // Définition du vertexBuffer
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glUseProgram(program);

    // Association des 3 1ères composantes des VertexData à la variable "vPos" du pipeline
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) 0);

    // Association des 3 composantes suivantes des VertexData à la variable "vNor" du pipeline  
    // glEnableVertexAttribArray(vnor_location);
    // glVertexAttribPointer(vnor_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) (sizeof(float) * 3));

    // Association des 2 composantes suivantes des VertexData à la variable "vTex" du pipeline  
    glEnableVertexAttribArray(vtex_location);
    glVertexAttribPointer(vtex_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) (sizeof(float) * 6));

    texUnit = 1;
    glUniform1i(tex_location, texUnit);
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Table::render(mat4 mvp)
{
    GLuint program = getProgram();
    GLint mvp_location = glGetUniformLocation(program, "MVP");
    glUseProgram(program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);

    // Selection du VertexArray
    glBindVertexArray(vertex_array);

    // Affichage des 3 1ers sommets en utilisant des triangles.
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}